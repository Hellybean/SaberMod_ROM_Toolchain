
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_java_awt_font_opentype_OpenTypeFont__
#define __gnu_java_awt_font_opentype_OpenTypeFont__

#pragma interface

#include <java/lang/Object.h>
#include <gcj/array.h>

extern "Java"
{
  namespace gnu
  {
    namespace java
    {
      namespace awt
      {
        namespace font
        {
          namespace opentype
          {
              class CharGlyphMap;
              class GlyphNamer;
              class Hinter;
              class OpenTypeFont;
              class Scaler;
            namespace truetype
            {
                class Zone;
            }
          }
        }
      }
    }
  }
  namespace java
  {
    namespace awt
    {
        class Font;
      namespace font
      {
          class FontRenderContext;
          class GlyphVector;
      }
      namespace geom
      {
          class AffineTransform;
          class GeneralPath;
          class Point2D;
      }
    }
    namespace nio
    {
        class ByteBuffer;
    }
    namespace text
    {
        class CharacterIterator;
    }
  }
}

class gnu::java::awt::font::opentype::OpenTypeFont : public ::java::lang::Object
{

public: // actually package-private
  OpenTypeFont(::java::nio::ByteBuffer *, jint);
private:
  jint getTableIndex(jint);
public:
  ::java::lang::String * getFamilyName(::java::util::Locale *);
  ::java::lang::String * getSubFamilyName(::java::util::Locale *);
  ::java::lang::String * getFullName(::java::util::Locale *);
  ::java::lang::String * getPostScriptName();
  jint getNumGlyphs();
  jint getMissingGlyphCode();
private:
  ::java::lang::String * getName(jint, ::java::util::Locale *);
public:
  jint getVersion();
  ::java::nio::ByteBuffer * getFontTable(jint);
  jint getFontTableSize(jint);
private:
  ::gnu::java::awt::font::opentype::CharGlyphMap * getCharGlyphMap();
public:
  jint getGlyph(jint);
  ::java::awt::font::GlyphVector * createGlyphVector(::java::awt::Font *, ::java::awt::font::FontRenderContext *, ::java::text::CharacterIterator *);
  jint getGlyphIndex(jint);
  void getAdvance(jint, jfloat, ::java::awt::geom::AffineTransform *, jboolean, jboolean, jboolean, ::java::awt::geom::Point2D *);
  ::java::awt::geom::GeneralPath * getGlyphOutline(jint, jfloat, ::java::awt::geom::AffineTransform *, jboolean, jboolean, jint);
  ::gnu::java::awt::font::opentype::truetype::Zone * getRawGlyphOutline(jint, ::java::awt::geom::AffineTransform *);
  ::java::lang::String * getGlyphName(jint);
  jfloat getAscent(jfloat, ::java::awt::geom::AffineTransform *, jboolean, jboolean, jboolean);
  jfloat getDescent(jfloat, ::java::awt::geom::AffineTransform *, jboolean, jboolean, jboolean);
public: // actually package-private
  static ::java::lang::String * tagToString(jint);
private:
  void checkHinter(jint);
public: // actually package-private
  static const jint TAG_OTTO = 1330926671;
  static const jint TAG_SFNT = 1936092788;
  static const jint TAG_TRUE = 1953658213;
  static const jint TAG_TTCF = 1953784678;
  static const jint TAG_ZAPF = 1516335206;
  ::java::nio::ByteBuffer * __attribute__((aligned(__alignof__( ::java::lang::Object)))) buf;
  jint numGlyphs;
  JArray< jint > * tableTag;
  JArray< jint > * tableStart;
  JArray< jint > * tableLength;
private:
  jint version;
public:
  jint unitsPerEm;
private:
  jfloat emsPerUnit;
  ::gnu::java::awt::font::opentype::Scaler * scaler;
  ::gnu::java::awt::font::opentype::CharGlyphMap * cmap;
  ::gnu::java::awt::font::opentype::GlyphNamer * glyphNamer;
  ::gnu::java::awt::font::opentype::Hinter * hinter;
  ::java::nio::ByteBuffer * nameTable;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_java_awt_font_opentype_OpenTypeFont__
