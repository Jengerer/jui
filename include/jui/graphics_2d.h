#ifndef GRAPHICS_2D_H
#define GRAPHICS_2D_H

#include "jui/colour.h"
#include "jui/file_texture.h"
#include "jui/iresource_source.h"
#include "jui/opengl_shared.h"
#include "jui/string_hasher.h"
#include "jui/window.h"

#include <hash_map>
#include <string>
#include <stdexcept>

typedef std::hash_map<std::string, FileTexture*, StringHasher> TextureMap;

class Graphics2D
{

public:

	__declspec(dllexport) Graphics2D( Window* window );
	__declspec(dllexport) ~Graphics2D( void );

	// Loading/closing interfaces.
	__declspec(dllexport) void initialize( void );
	void clean_up( void );

	// Scene initialization.
	void setup_scene();
	void resize_scene( GLsizei width, GLsizei height );

	// Buffer handling.
	__declspec(dllexport) void clear_scene();
	__declspec(dllexport) void swap_buffers();

	// Resource handling.
	__declspec(dllexport) Texture*		create_empty_texture( GLsizei width, GLsizei height, GLenum format );
	__declspec(dllexport) GLuint		create_texture( GLubyte* data, GLsizei width, GLsizei height, GLenum format );
	__declspec(dllexport) FileTexture*	get_texture( const std::string& filename );

	// Drawing functions.
	__declspec(dllexport) void draw_rectangle( GLfloat x, GLfloat y, GLfloat width, GLfloat height );
	__declspec(dllexport) void draw_texture( const Texture* texture, GLfloat x, GLfloat y );
	__declspec(dllexport) void draw_texture( const Texture* texture, GLfloat x, GLfloat y, GLsizei width, GLsizei height );
	__declspec(dllexport) void draw_display_list( GLuint list, GLfloat x, GLfloat y );

	// Line loop functions.
	__declspec(dllexport) void begin( GLenum mode ) const;
	__declspec(dllexport) void draw_vertex( float x, float y ) const;
	__declspec(dllexport) void end() const;

	// Drawing state functions.
	__declspec(dllexport) void translate( float x, float y ) const;

	// Drawing matrix handling.
	__declspec(dllexport) void push_matrix() const;
	__declspec(dllexport) void pop_matrix() const;

	// Setting render context.
	__declspec(dllexport) HGLRC get_render_context() const;
	__declspec(dllexport) HGLRC get_loading_context() const;
	__declspec(dllexport) bool set_render_context( HGLRC context );
	__declspec(dllexport) bool unset_render_context();

	// Render mode handling.
	__declspec(dllexport) void set_blend_state( GLenum src_blend, GLenum dest_blend );
	__declspec(dllexport) void set_colour( const Colour& colour );

	// Framebuffer handling.
	__declspec(dllexport) void render_to_texture( const Texture* texture );
	__declspec(dllexport) void reset_render_target();

private:

	// Resource handling.
	void load_texture( FileTexture* texture );

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

#endif // GRAPHICS_2D_H