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
	class __declspec(dllexport) Graphics2D
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

		Graphics2D( Window* window );
		~Graphics2D( void );

		// Loading/closing interfaces.
		ReturnStatus initialize( void );
		ReturnStatus clean_up( void );

		// Scene initialization.
		void setup_scene( void );
		void resize_scene( GLsizei width, GLsizei height );

		// Buffer handling.
		void clear_scene( void );
		void swap_buffers( void );

		// Resource handling.
		Texture* create_empty_texture( GLsizei width, GLsizei height, GLenum format );
		GLuint create_texture( GLubyte* data, GLsizei width, GLsizei height, GLenum format );
		ReturnStatus get_texture( const JUTIL::String* filename, FileTexture** output );

		// Drawing functions.
		void draw_pixel( int x, int y, const Colour& colour );
		void draw_rectangle( int x, int y, int width, int height );
		void draw_rounded_rectangle( int x, int y, int width, int height, int radius );
		void draw_rounded_rectangle_border( int x, int y, int width, int height, int radius, int stroke_size );
		void draw_texture( const Texture* texture, int x, int y );
		void draw_texture( const Texture* texture, int x, int y, int width, int height );
		void draw_display_list( GLuint list, int x, int y );

		// Line loop functions.
		void begin( GLenum mode ) const;
		void draw_vertex( int x, int y ) const;
		void end( void ) const;

		// Drawing state functions.
		void translate( int x, int y ) const;

		// Drawing matrix handling.
		void push_matrix( void ) const;
		void pop_matrix( void ) const;

		// Setting render context.
		HGLRC get_render_context( void ) const;
		HGLRC get_loading_context( void ) const;
		bool set_render_context( HGLRC context );
		bool unset_render_context( void );

		// Render mode handling.
		void set_blend_state( GLenum src_blend, GLenum dest_blend );
		void set_colour( const Colour& colour );

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

		// Framebuffer variables.
		GLuint fbo_;

		// Texture map.
		TextureMap textures_;

	};

}

#endif // GRAPHICS_2D_HPP
