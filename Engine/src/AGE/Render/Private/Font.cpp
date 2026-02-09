#include "AGEpch.hpp"
#include "Render/Public/Font.h"
#include "Statics/Public/Statics.h"
#include "Core/Public/App.h"

#undef INFINITE
#include "msdf-atlas-gen/msdf-atlas-gen.h"
#include "msdf-atlas-gen/FontGeometry.h"
#include "msdf-atlas-gen/GlyphGeometry.h"

#include "Core/Public/Buffer.h"

#include "Render/Public/MSDFData.h"

namespace AGE
{
	template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
	static Ref<Texture2D> CreateAndCacheAtlas(const std::string& FontName, float FontSize, const std::vector<msdf_atlas::GlyphGeometry>& Glyphs,
		const msdf_atlas::FontGeometry& FontGeometry, uint32_t Width, uint32_t Height)
	{
		msdf_atlas::GeneratorAttributes Attributes;
		Attributes.config.overlapSupport = true;
		Attributes.scanlinePass = true;

		msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> Generator(Width, Height);
		Generator.setAttributes(Attributes);
		Generator.setThreadCount(8);
		Generator.generate(Glyphs.data(), (int)Glyphs.size());

		msdfgen::BitmapConstRef<T, N> BitMap = (msdfgen::BitmapConstRef<T, N>)Generator.atlasStorage();

		TextureSpecification Spec;
		Spec.Width = BitMap.width;
		Spec.Height = BitMap.height;
		Spec.Format = ImageFormat::RGB8;
		Spec.GenerateMips = false;


		Ref<Texture2D> Texture = Texture2D::Create(Spec);
		Texture->SetData((void*)BitMap.pixels, BitMap.width * BitMap.height * 3);
		Texture->SetName(FontName);
		return Texture;
	}



	Font::Font(const std::filesystem::path& FontPath)
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
					uint64_t GlyphSeed = (LCG_MULTIPLIER * (ColoringSeed ^ i) + LCG_INCREMENT) * !!ColoringSeed;
					Glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, GlyphSeed);
					return true;
				}, m_Data->Glyphs.size()).finish(THREAD_COUNT);
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

		m_AtlasTexture = CreateAndCacheAtlas<uint8_t, float, 3, msdf_atlas::msdfGenerator>(Utils::EngineStatics::GetFilename(Path), (float)EmSize, m_Data->Glyphs, m_Data->FontGeometry, width, height);
		m_AtlasTexture->SetTextureFilePath(FontPath.string());
		SaveFont();

		msdfgen::destroyFont(Font);
		msdfgen::deinitializeFreetype(FT);
		m_AtlasTexture.reset();

	}
	Font::~Font()
	{
		delete m_Data;
	}

	void Font::SaveFont() const
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

	void Font::LoadFont(const std::string& FontName)
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
		m_AtlasTexture->SetData(TextureBytes.Data, TextureBytes.Size);
		CoreLogger::Info("Loaded Font {}", FontName);
	}

	Ref<Font> Font::GetDefault()
	{
		static Ref<Font> DefaultFont;

		if (!DefaultFont)
		{
			AppConfig Config = App::Get().GetAppConfig();
			DefaultFont = CreateRef<Font>(Config.DefaultFontPath.string());
			//DefaultFont = CreateRef<Font>(g_EditorAssetPath.string() +"/Fonts/Open_Sans/static/OpenSans-Regular.ttf");

			return DefaultFont;
		}
		return DefaultFont;
	}
}