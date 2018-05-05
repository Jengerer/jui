#ifndef GRAPHICS_2D_HPP
#define GRAPHICS_2D_HPP

#include "jui/application/window.hpp"
#include "jui/gfx/colour.hpp"
#include "jui/gfx/file_texture.hpp"
#include "jui/gfx/opengl_shared.hpp"
#include "jui/net/resource_source_interface.hpp"

#include <string/constant_string.hpp>
#include <string/string_hasher.hpp>
#include <containers/hash_map.hpp>

namespace JUI
{

	// Data structure control textures.
	typedef JUTIL::HashMap<int, const JUTIL::String*, FileTexture*, JUTIL::StringHasher> TextureMap;

	/*
	 * Class for managing a 2D rendering surfaces.
	 */
	class Graphics2D
	{

	public:

		// Return codes for graphics functions.
		enum ReturnStatus
		{
			Success = 0,
			GetDCFailure,   // Failed to get device context for window.
			ReleaseDCFailure,
			ChangeDisplaySettingsFailure,
			ChoosePixelFormatFailure,
			SetPixelFormatFailure,
			CreateRCFailure,
			ShareListsFailure,
			SetRCFailure,
			UnsetRCFailure,
			DeleteRCFailure,

			// Texture errors.
			OpenTextureFailure,
			ReadPNGFormatFailure,
			NoMemoryForTextureFailure,
		};

	public:

		JUI_API Graphics2D( Window* window );
		JUI_API ~Graphics2D( void );

		// Loading/closing interfaces.
		JUI_API ReturnStatus initialize( void );
		JUI_API ReturnStatus clean_up( void );

		// Scene initialization.
		JUI_API void setup_scene( void );
		JUI_API void resize_scene( GLsizei width, GLsizei height );

		// Buffer handling.
		JUI_API void clear_scene( void );
		JUI_API void swap_buffers( void );

		// Resource handling.
		JUI_API Texture* create_empty_texture( GLsizei width, GLsizei height, GLenum format );
		JUI_API GLuint create_texture( GLubyte* data, GLsizei width, GLsizei height, GLenum format );
		JUI_API ReturnStatus get_texture( const JUTIL::String* filename, FileTexture** output );

		// Drawing functions.
		JUI_API void draw_pixel( int x, int y, const Colour* colour );
		JUI_API void draw_rectangle( int x, int y, int width, int height );
		JUI_API void draw_rounded_rectangle( int x, int y, int width, int height, int radius );
		JUI_API void draw_rounded_rectangle_border( int x, int y, int width, int height, int radius, int stroke_size );
		JUI_API void draw_texture( const Texture* texture, int x, int y );
		JUI_API void draw_texture( const Texture* texture, int x, int y, int width, int height );

		JUI_API void draw_texture_restricted( const Texture* texture, int x, int y, 
			int restricted_x, int restricted_y, int restricted_width, int restricted_height );
		JUI_API void draw_texture_restricted( const Texture* texture, int x, int y, int width, int height, 
			int restricted_x, int restricted_y, int restricted_width, int restricted_height );

		JUI_API void draw_display_list( GLuint list, int x, int y );

		// Line loop functions.
		JUI_API void begin( GLenum mode ) const;
		JUI_API void draw_vertex( int x, int y ) const;
		JUI_API void end( void ) const;

		// Drawing state functions.
		JUI_API void translate( int x, int y ) const;

		// Drawing matrix handling.
		JUI_API void push_matrix( void ) const;
		JUI_API void pop_matrix( void ) const;

		// Setting render context.
		HGLRC get_render_context( void ) const;
		JUI_API HGLRC get_loading_context( void ) const;
		JUI_API bool set_render_context( HGLRC context );
		bool unset_render_context( void );

		// Render mode handling.
		void set_blend_state( GLenum src_blend, GLenum dest_blend );
		void set_blend_alpha( float alpha );
		float get_blend_alpha( void ) const;
		JUI_API void set_colour( const Colour* colour );

		// Framebuffer handling.
		void render_to_texture( const Texture* texture );
		void reset_render_target( void );

	private:

		// Helper for rounded rectangles.
		void draw_circle( int x, int y, int radius, GLfloat start_angle, GLfloat step, unsigned int step_count ) const;

		// Resource handling.
		ReturnStatus load_texture( FileTexture* texture );

	public:

		HGLRC loading_rc_;
		HDC dc_;

	private:

		// Window variables.
		Window* window_;

		// OpenGL contexts.
		HGLRC rc_;

		// Rendering members.
		GLuint fbo_;
		JUI::Colour colour_;
		float blend_alpha_;

		// Texture map.
		TextureMap textures_;

	};

}

#endif // GRAPHICS_2D_HPP
