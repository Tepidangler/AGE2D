//
// Created by De'Lano Wilcox on 11/22/2025.
//
#pragma once
#ifndef AGE_SOUNDBANK_H
#define AGE_SOUNDBANK_H

#endif //AGE_SOUNDBANK_H

#include "Core/Public/UUID.h"
#include <string>
#include <filesystem>

namespace AGE
{
	class SoundBank
	{
	public:
		SoundBank(const std::filesystem::path& FilePath, UUID ID);
		/**
 * @brief Default copy constructor for the SoundBank class.
 *
 * This function is used to create a new instance of the SoundBank class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler.
 * 
 * @param[in] other The SoundBank object to be copied.
 * 
 * @return A new instance of the SoundBank class with the same data as the input parameter.
 */
/**
 * @brief Default copy constructor for the SoundBank class.
 *
 * This function is used to create a new instance of the SoundBank class by copying an existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this member function.
 *
 * @param other The SoundBank object to be copied.
 * 
 * @return A new SoundBank instance that is a copy of the input SoundBank.
 */
SoundBank(const SoundBank&) = default;
		/**
 * @brief Default destructor for the SoundBank class.
 *
 * This function is used to clean up any resources that the SoundBank object may be using, such as memory or file handles. It's important to ensure that all resources are properly released when they are no longer needed to prevent potential memory leaks or other issues. 
 *
 * @return void
 */
/**
 * @brief Destructor for the SoundBank class.
 *
 * This function is responsible for releasing any resources that were acquired by the SoundBank object, such as memory or file handles. It does not return anything and has no parameters.
 */
~SoundBank() = default;

		/**
 * @brief Returns the file path of the object.
 * @return A reference to the file path member variable.
 */
/**
 * @brief Returns the file path of the object.
 * @return A reference to a std::filesystem::path object representing the file path.
 */
std::filesystem::path& GetFilePath() {return m_FilePath; }
		/**
 * @brief Returns the name of the bank.
 * @return A reference to a string containing the name of the bank.
 */
/**
 * @brief Gets the name of a bank.
 *
 * This function returns a reference to the private member variable `m_Name`, which holds the name of the bank.
 * The returned value is non-const and can be modified by the caller. However, it's important to note that any changes made to this string will affect the internal state of the object.
 * 
 * @return A reference to a string containing the name of the bank.
 */
std::string& GetBankName() {return m_Name;}
		/**
 * @brief This function sets the bank name.
 * @param Name The new name of the bank.
 */
/**
 * @brief Sets the bank name.
 *
 * This function sets the bank name by assigning it to the member variable m_Name.
 * The parameter 'Name' is a const reference to std::string, which represents the new bank name.
 * 
 * @param Name A const reference to std::string representing the new bank name.
 */
void SetBankName(const std::string& Name) {m_Name = Name;};
		/**
 * @brief This function returns the bank ID of the current object.
 * @return uint32_t The bank ID as a 32-bit unsigned integer.
 */
/**
 * @brief Retrieves the bank ID of the object.
 * @return The bank ID as a uint32_t value.
 */
uint32_t GetBankID() {return m_ID;}
		/**
 * @brief This function sets the bank ID to a given value.
 * @param ID The new uint32_t type ID that will be set for the bank.
 */
/**
 * @brief This function sets the bank identifier with a given uint32 value.
 * @param ID The unique identifier of the bank to be set.
 */
void SetBankID(uint32_t ID) {m_ID = ID;}

		/**
 * @brief Gets the Asset ID of the object.
 *
 * This function returns a reference to the private member variable 'm_AssetID'. It is used to access and possibly modify it if necessary. 
 * The returned value should not be altered as it may affect other parts of the program that rely on this unique identifier for their operations.
 *
 * @return A reference to UUID& representing the Asset ID.
 */
/**
 * @brief Gets the Asset ID of the object.
 *
 * This function returns a reference to the private member variable 'm_AssetID'. It is used to access and possibly modify this value if necessary. 
 *
 * @return A reference to UUID& representing the Asset ID.
 */
UUID& GetAssetID() {return m_AssetID;}

		std::filesystem::path m_FilePath;
		std::string m_Name;
		uint32_t m_ID;
		UUID m_AssetID;
	};


}
