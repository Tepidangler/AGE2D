#include "AGEpch.hpp"
#include "Render/Public/Font.h"
#include "Statics/Public/Statics.h"
#include "Core/Public/App.h"

#undef INFINITE
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wfloat-conversion"
#pragma clang diagnostic ignored "-Wsign-conversion"
#include "msdf-atlas-gen/msdf-atlas-gen.h"
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "msdf-atlas-gen/msdf-atlas-gen.h"
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include "msdf-atlas-gen/msdf-atlas-gen.h"
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif
#include "msdf-atlas-gen/FontGeometry.h"
#include "msdf-atlas-gen/GlyphGeometry.h"

#include "Core/Public/Buffer.h"

#include "Render/Public/MSDFData.h"

namespace AGE
{
	template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
	"Creates and caches an MSDF (Multiple Signed Distance Field) atlas from glyphs and font geometry."
static Ref<Texture2D> CreateAndCacheAtlas(const std::string& FontName, float FontSize, const std::vector<msdf_atlas::GlyphGeometry>& Glyphs,
		const msdf_atlas::FontGeometry& FontGeometry, uint32_t Width, uint32_t Height)
	{
		msdf_atlas::GeneratorAttributes Attributes;
		Attributes.config.overlapSupport = true;
		Attributes.scanlinePass = true;

		msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> Generator((int)Width, (int)Height);
		Generator.setAttributes(Attributes);
		Generator.setThreadCount(8);
		Generator.generate(Glyphs.data(), (int)Glyphs.size());

		msdfgen::BitmapConstRef<T, N> BitMap = (msdfgen::BitmapConstRef<T, N>)Generator.atlasStorage();

		TextureSpecification Spec;
		Spec.Width = (uint32_t)BitMap.width;
		Spec.Height = (uint32_t)BitMap.height;
		Spec.Format = ImageFormat::RGB8;
		Spec.GenerateMips = false;


		Ref<Texture2D> Texture = Texture2D::Create(Spec);
		Texture->SetData((void*)BitMap.pixels, (uint32_t)(BitMap.width * BitMap.height * 3));
		Texture->SetName(FontName);
		return Texture;
	}



	/**
 * @brief Initializes an instance of AGEFont with a specified font file.
 *
 * This constructor loads a font from the provided file path, and prepares it for rendering by generating MSDF data 
 * and creating an atlas texture. The font is loaded if its corresponding .AGEfont file exists in the editor assets directory.
 * If not, the font is loaded directly from the given file path using msdfgen library functions.
 *
 * @param FontPath The filesystem path to the font file.
 */
AGEFont::AGEFont(const std::filesystem::path& FontPath)
		:m_Data(new MSDFData())
	{
		std::filesystem::path Path = FontPath;
		const std::string FontName = Utils::EngineStatics::GetFilename(Path);
		const AppConfig& Config = App::Get().GetAppConfig();
		if (std::filesystem::exists(Config.EditorAssetPath/std::vformat("Fonts/AGEFonts/{}.AGEfont", std::make_format_args(FontName))))
		{
			LoadFont(FontName);
			return;
		}
		msdfgen::FreetypeHandle* FT = msdfgen::initializeFreetype();

		CoreLogger::Assert(FT, "Unable to Initialize FreeType!");

		std::string FileString = FontPath.string();
		msdfgen::FontHandle* Font = msdfgen::loadFont(FT, FileString.c_str());
		if (!Font)
		{
			CoreLogger::Error("Failed to load font: {}", FileString);
			return;
		}

		struct CharsetRange
		{
			uint32_t Begin, End;
		};

		static constexpr CharsetRange CharsetRanges[] = { { 0x0020, 0x00FF } };

		msdf_atlas::Charset CharSet;

		for (CharsetRange Range : CharsetRanges)
		{
			for (uint32_t c = Range.Begin; c <= Range.End; c++)
			{
				CharSet.add(c);
			}
		}
		double FontScale = 1.0;
		m_Data->FontGeometry = msdf_atlas::FontGeometry(&m_Data->Glyphs);
		int GlpyhsLoaded = m_Data->FontGeometry.loadCharset(Font, FontScale, CharSet);
		CoreLogger::Info("Loaded {0} glyphs from font (out of {1})", GlpyhsLoaded, CharSet.size());

		double EmSize = 40.0;

		msdf_atlas::TightAtlasPacker AtlasPacker;
		AtlasPacker.setPixelRange(2.0);
		AtlasPacker.setMiterLimit(1.0);
		//AtlasPacker.setPadding(0); // Find Alternative
		AtlasPacker.setScale(EmSize);
		int Remaining = AtlasPacker.pack(m_Data->Glyphs.data(), (int)m_Data->Glyphs.size());
		CoreLogger::Assert(Remaining == 0, "{} Glyphs remaining", Remaining);
		int width, height;
		AtlasPacker.getDimensions(width, height);
		EmSize = AtlasPacker.getScale();

#define DEFAULT_ANGLE_THRESHOLD 3.0
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define THREAD_COUNT 8

		uint64_t ColoringSeed = 0;
		bool ExpensiveColoring = false;

		if (ExpensiveColoring)
		{
			msdf_atlas::Workload([&Glyphs = m_Data->Glyphs, &ColoringSeed](int i, int ThreadNo) -> bool
				{
					uint64_t GlyphSeed = (LCG_MULTIPLIER * (ColoringSeed ^ (uint64_t)i) + LCG_INCREMENT) * !!ColoringSeed;
					Glyphs[(size_t)i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, GlyphSeed);
					return true;
				}, (int)m_Data->Glyphs.size()).finish(THREAD_COUNT);
		}
		else
		{
			uint64_t GlyphSeed = ColoringSeed;
			for (msdf_atlas::GlyphGeometry& Glyph : m_Data->Glyphs)
			{
				GlyphSeed *= LCG_MULTIPLIER;
				Glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, GlyphSeed);
			}
		}

		m_AtlasTexture = CreateAndCacheAtlas<uint8_t, float, 3, msdf_atlas::msdfGenerator>(Utils::EngineStatics::GetFilename(Path), (float)EmSize, m_Data->Glyphs, m_Data->FontGeometry, (uint32_t)width, (uint32_t)height);
		m_AtlasTexture->SetTextureFilePath(FontPath.string());
		SaveFont();

		msdfgen::destroyFont(Font);
		msdfgen::deinitializeFreetype(FT);
		m_AtlasTexture.reset();

	}
	/**
 * @brief Destructor for AGEFont class. Deletes the memory allocated to store font data.
 */
AGEFont::~AGEFont()
	{
		delete m_Data;
	}

	/**
 * @brief Saves the font data to a file.
 * 
 * This function writes the font data into a file in the specified location. The format of the written data is as follows:
 * - A string "AGEFont" identifying the type of the saved data.
 * - An unsigned 16-bit integer representing the version number (currently set to 1).
 * - A TextureSpecification object containing information about the font texture.
 * - The raw bytes of the font texture.
 * 
 * @return void
 */
void AGEFont::SaveFont() const
	{
		const AppConfig& Config = App::Get().GetAppConfig();
		const std::string& FileName = m_AtlasTexture->GetName();
		FileStreamWriter FontData(Config.EditorAssetPath/std::vformat("Fonts/AGEFonts/{}.AGEfont", std::make_format_args(FileName)));

		FontData.WriteString("AGEFont");
		FontData.WriteRaw<uint16_t>(1);
		TextureSpecification FontSpec = m_AtlasTexture->GetSpecification();
		FontData.WriteObject<TextureSpecification>(FontSpec);
		Buffer TextureBytes(m_AtlasTexture->GetTextureData().first, m_AtlasTexture->GetTextureData().second);
		FontData.WriteBuffer(TextureBytes);
	}

	
void AGEFont::LoadFont(const std::string& FontName)
	{
		const AppConfig& Config = App::Get().GetAppConfig();
		const std::string& FileName = FontName;
		FileStreamReader FontData(Config.EditorAssetPath/std::vformat("Fonts/AGEFonts/{}.AGEfont", std::make_format_args(FileName)));

		std::string Header;
		FontData.ReadString(Header);
		if (Header.compare("AGEFont") != 0)
		{
			CoreLogger::Error("Font File is corrupted");
			return;
		}
		uint16_t version; //While not in this particular version, in other versions of this engine, these version numbers are subject to change, so we write them so we can easily make our files backwards compatible
		FontData.ReadRaw<uint16_t>(version);
		TextureSpecification FontSpec{};
		FontData.ReadObject<TextureSpecification>(FontSpec);
		size_t Size;
		FontData.ReadRaw<size_t>(Size);
		Buffer TextureBytes;
		TextureBytes.Allocate(Size);
		FontData.ReadBuffer((char*)TextureBytes.Data, TextureBytes.Size);
		m_AtlasTexture = Texture2D::Create(FontSpec);
		m_AtlasTexture->SetData(TextureBytes.Data, (uint32_t)TextureBytes.Size);
		CoreLogger::Info("Loaded Font {}", FontName);
	}

	/**
 * @brief GetDefault returns the default font instance. If it doesn't exist, a new one is created and returned.
 * 
 * @return Ref<AGEFont> A reference to the default font instance.
 */
Ref<AGEFont> AGEFont::GetDefault()
	{
		static Ref<AGEFont> DefaultFont;

		if (!DefaultFont)
		{
			AppConfig Config = App::Get().GetAppConfig();
			DefaultFont = CreateRef<AGEFont>(Config.DefaultFontPath.string());
			//DefaultFont = CreateRef<Font>(g_EditorAssetPath.string() +"/Fonts/Open_Sans/static/OpenSans-Regular.ttf");

			return DefaultFont;
		}
		return DefaultFont;
	}
}