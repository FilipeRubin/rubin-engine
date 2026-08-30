#pragma once

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef void GLvoid;
typedef signed long long int GLsizeiptr;
typedef char GLchar;

// GL_VERSION_1_0
#define GL_DEPTH_BUFFER_BIT       0x00000100
#define GL_STENCIL_BUFFER_BIT     0x00000400
#define GL_COLOR_BUFFER_BIT       0x00004000
#define GL_FALSE                  0
#define GL_TRUE                   1
#define GL_POINTS                 0x0000
#define GL_LINES                  0x0001
#define GL_LINE_LOOP              0x0002
#define GL_LINE_STRIP             0x0003
#define GL_TRIANGLES              0x0004
#define GL_TRIANGLE_STRIP         0x0005
#define GL_TRIANGLE_FAN           0x0006
#define GL_FRONT                  0x0404
#define GL_BACK                   0x0405
#define GL_LEFT                   0x0406
#define GL_RIGHT                  0x0407
#define GL_FRONT_AND_BACK         0x0408
#define GL_CW                     0x0900
#define GL_CCW                    0x0901
#define GL_CULL_FACE              0x0B44
#define GL_DEPTH_TEST             0x0B71
#define GL_STENCIL_TEST           0x0B90
#define GL_UNPACK_SWAP_BYTES      0x0CF0
#define GL_UNPACK_LSB_FIRST       0x0CF1
#define GL_UNPACK_ROW_LENGTH      0x0CF2
#define GL_UNPACK_SKIP_ROWS       0x0CF3
#define GL_UNPACK_SKIP_PIXELS     0x0CF4
#define GL_UNPACK_ALIGNMENT       0x0CF5
#define GL_PACK_SWAP_BYTES        0x0D00
#define GL_PACK_LSB_FIRST         0x0D01
#define GL_PACK_ROW_LENGTH        0x0D02
#define GL_PACK_SKIP_ROWS         0x0D03
#define GL_PACK_SKIP_PIXELS       0x0D04
#define GL_PACK_ALIGNMENT         0x0D05
#define GL_TEXTURE_1D             0x0DE0
#define GL_TEXTURE_2D             0x0DE1
#define GL_TEXTURE_WIDTH          0x1000
#define GL_TEXTURE_HEIGHT         0x1001
#define GL_TEXTURE_BORDER_COLOR   0x1004
#define GL_BYTE                   0x1400
#define GL_UNSIGNED_BYTE          0x1401
#define GL_SHORT                  0x1402
#define GL_UNSIGNED_SHORT         0x1403
#define GL_INT                    0x1404
#define GL_UNSIGNED_INT           0x1405
#define GL_FLOAT                  0x1406
#define GL_RED                    0x1903
#define GL_GREEN                  0x1904
#define GL_BLUE                   0x1905
#define GL_ALPHA                  0x1906
#define GL_RGB                    0x1907
#define GL_RGBA                   0x1908
#define GL_VENDOR                 0x1F00
#define GL_RENDERER               0x1F01
#define GL_VERSION                0x1F02
#define GL_NEAREST                0x2600
#define GL_LINEAR                 0x2601
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_LINEAR_MIPMAP_NEAREST  0x2701
#define GL_NEAREST_MIPMAP_LINEAR  0x2702
#define GL_LINEAR_MIPMAP_LINEAR   0x2703
#define GL_TEXTURE_MAG_FILTER     0x2800
#define GL_TEXTURE_MIN_FILTER     0x2801
#define GL_TEXTURE_WRAP_S         0x2802
#define GL_TEXTURE_WRAP_T         0x2803
#define GL_REPEAT                 0x2901

// GL_VERSION_1_1
#define GL_DOUBLE   0x140A
#define GL_R3_G3_B2 0x2A10
#define GL_RGB4     0x804F
#define GL_RGB5     0x8050
#define GL_RGB8     0x8051
#define GL_RGB10    0x8052
#define GL_RGB12    0x8053
#define GL_RGB16    0x8054
#define GL_RGBA2    0x8055
#define GL_RGBA4    0x8056
#define GL_RGB5_A1  0x8057
#define GL_RGBA8    0x8058
#define GL_RGB10_A2 0x8059
#define GL_RGBA12   0x805A
#define GL_RGBA16   0x805B

// GL_VERSION_1_2
#define GL_UNSIGNED_BYTE_3_3_2     0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4  0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1  0x8034
#define GL_UNSIGNED_INT_8_8_8_8    0x8035
#define GL_UNSIGNED_INT_10_10_10_2 0x8036

// GL_VERSION_1_3
#define GL_TEXTURE0    0x84C0
#define GL_TEXTURE1    0x84C1
#define GL_TEXTURE2    0x84C2
#define GL_TEXTURE3    0x84C3
#define GL_TEXTURE4    0x84C4
#define GL_TEXTURE5    0x84C5
#define GL_TEXTURE6    0x84C6
#define GL_TEXTURE7    0x84C7
#define GL_TEXTURE8    0x84C8
#define GL_TEXTURE9    0x84C9
#define GL_TEXTURE10   0x84CA
#define GL_TEXTURE11   0x84CB
#define GL_TEXTURE12   0x84CC
#define GL_TEXTURE13   0x84CD
#define GL_TEXTURE14   0x84CE
#define GL_TEXTURE15   0x84CF
#define GL_TEXTURE16   0x84D0
#define GL_TEXTURE17   0x84D1
#define GL_TEXTURE18   0x84D2
#define GL_TEXTURE19   0x84D3
#define GL_TEXTURE20   0x84D4
#define GL_TEXTURE21   0x84D5
#define GL_TEXTURE22   0x84D6
#define GL_TEXTURE23   0x84D7
#define GL_TEXTURE24   0x84D8
#define GL_TEXTURE25   0x84D9
#define GL_TEXTURE26   0x84DA
#define GL_TEXTURE27   0x84DB
#define GL_TEXTURE28   0x84DC
#define GL_TEXTURE29   0x84DD
#define GL_TEXTURE30   0x84DE
#define GL_TEXTURE31   0x84DF
#define GL_MULTISAMPLE 0x809D

// GL_VERSION_1_5
#define GL_ARRAY_BUFFER         0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_STREAM_DRAW          0x88E0
#define GL_STREAM_READ          0x88E1
#define GL_STREAM_COPY          0x88E2
#define GL_STATIC_DRAW          0x88E4
#define GL_STATIC_READ          0x88E5
#define GL_STATIC_COPY          0x88E6
#define GL_DYNAMIC_DRAW         0x88E8
#define GL_DYNAMIC_READ         0x88E9
#define GL_DYNAMIC_COPY         0x88EA

// GL_VERSION_2_0
#define GL_FRAGMENT_SHADER      0x8B30
#define GL_VERTEX_SHADER        0x8B31
#define GL_SHADER_TYPE          0x8B4F
#define GL_DELETE_STATUS        0x8B80
#define GL_COMPILE_STATUS       0x8B81
#define GL_LINK_STATUS          0x8B82
#define GL_INFO_LOG_LENGTH      0x8B84
#define GL_SHADER_SOURCE_LENGTH 0x8B88

// GL_VERSION_3_0
#define GL_RGBA32F    0x8814
#define GL_RGB32F     0x8815
#define GL_RGBA16F    0x881A
#define GL_RGB16F     0x881B
#define GL_RG         0x8227
#define GL_RG_INTEGER 0x8228
#define GL_R8         0x8229
#define GL_R16        0x822A
#define GL_RG8        0x822B
#define GL_RG16       0x822C
#define GL_R16F       0x822D
#define GL_R32F       0x822E
#define GL_RG16F      0x822F
#define GL_RG32F      0x8230
#define GL_R8I        0x8231
#define GL_R8UI       0x8232
#define GL_R16I       0x8233
#define GL_R16UI      0x8234
#define GL_R32I       0x8235
#define GL_R32UI      0x8236
#define GL_RG8I       0x8237
#define GL_RG8UI      0x8238
#define GL_RG16I      0x8239
#define GL_RG16UI     0x823A
#define GL_RG32I      0x823B
#define GL_RG32UI     0x823C

// GL_VERSION_3_1
#define GL_COPY_READ_BUFFER  0x8F36
#define GL_COPY_WRITE_BUFFER 0x8F37
#define GL_UNIFORM_BUFFER    0x8A11

// GL_VERSION_3_2
#define GL_GEOMETRY_SHADER 0x8DD9

bool TryLoadOGL();
const void* CreateContext(const void* windowHandle, const void* sharedContext = nullptr);
void UnloadOGL();

extern void          (*glActiveTexture)(GLenum texture);
extern void          (*glAttachShader)(GLuint program, GLuint shader);
extern void          (*glBindBuffer)(GLenum target, GLuint buffer);
extern void          (*glBindTexture)(GLenum target, GLuint texture);
extern void          (*glBindVertexArray)(GLuint array);
extern void          (*glBufferData)(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
extern void          (*glClear)(GLbitfield mask);
extern void          (*glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern void          (*glCompileShader)(GLuint shader);
extern GLuint        (*glCreateProgram)();
extern GLuint        (*glCreateShader)(GLenum shaderType);
extern void          (*glCullFace)(GLenum mode);
extern void          (*glDeleteBuffers)(GLsizei n, GLuint* arrays);
extern void          (*glDeleteProgram)(GLuint program);
extern void          (*glDeleteShader)(GLuint shader);
extern void          (*glDeleteTextures)(GLsizei n, const GLuint* textures);
extern void          (*glDeleteVertexArrays)(GLsizei n, GLuint* arrays);
extern void          (*glDisable)(GLenum cap);
extern void          (*glDrawArrays)(GLenum mode, GLint first, GLsizei count);
extern void          (*glDrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
extern void          (*glEnable)(GLenum cap);
extern void          (*glEnableVertexAttribArray)(GLuint index);
extern void          (*glGenBuffers)(GLsizei n, GLuint* buffers);
extern void          (*glGenerateMipmap)(GLenum target);
extern void          (*glGenTextures)(GLsizei n, GLuint* textures);
extern void          (*glGenVertexArrays)(GLsizei n, GLuint* arrays);
extern void          (*glGetProgramInfoLog)(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
extern void          (*glGetProgramiv)(GLuint program, GLenum pname, GLint* params);
extern void          (*glGetShaderInfoLog)(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
extern void          (*glGetShaderiv)(GLuint shader, GLenum pname, GLint* params);
extern const GLubyte*(*glGetString)(GLenum name);
extern GLint         (*glGetUniformLocation)(GLuint program, const GLchar* name);
extern GLboolean     (*glIsProgram)(GLuint program);
extern GLboolean     (*glIsVertexArray)(GLuint array);
extern void          (*glLinkProgram)(GLuint program);
extern void          (*glPixelStorei)(GLenum pname, GLint param);
extern void          (*glShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
extern void          (*glTexImage2D)(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);
extern void          (*glTexParameteri)(GLenum target, GLenum pname, GLint param);
extern void          (*glUseProgram)(GLuint program);
extern void          (*glUniform3fv)(GLint location, GLsizei count, const GLfloat* value);
extern void          (*glUniform4fv)(GLint location, GLsizei count, const GLfloat* value);
extern void          (*glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
extern void          (*glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
extern void          (*glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
extern void          (*glViewport)(GLint x, GLint y, GLsizei width, GLsizei height);
