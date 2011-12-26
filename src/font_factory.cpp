#include "jui/font_factory.h"

FT_Library FontFactory::library_ = nullptr;

/*
 * Create library if not initialized.
 */
void FontFactory::initialize()
{
	// Load library.
	if (library_ == nullptr) {
		FT_Error error = FT_Init_FreeType( &library_ );
		if (error != 0) {
			throw std::runtime_error( "Failed to initialize FreeType library." );
		}
	}
}

/*
 * Close library.
 */
void FontFactory::shut_down()
{
	// Unload library.
	if (library_ != nullptr) {
		FT_Done_FreeType( library_ );
		library_ = nullptr;
	}
}

/*
 * Generate font for file name and size.
 */
Font* FontFactory::create_font( const std::string& filename, FT_F26Dot6 height )
{
	// Create font.
	FT_Face face;
	FT_Error error = FT_New_Face( library_, filename.c_str(), 0, &face );

	// Fault and reload on fail.
	if (error != FT_Err_Ok) {
		throw std::runtime_error( "Failed to load font: " + filename + "!" );
	}

	// Set character height.
	FT_Set_Char_Size( face, 0, height << 6, 96, 96 );

	// Create font.
	Font* font = new Font( face );
	font->generate_glyphs();

	// Return face.
	FT_Done_Face( face );
	return font;
}