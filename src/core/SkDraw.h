
/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkDraw_DEFINED
#define SkDraw_DEFINED

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkStrokeRec.h"
#include "src/core/SkDrawBase.h"
#include "src/core/SkGlyphRunPainter.h"
#include "src/core/SkMask.h"

class SkBitmap;
class SkClipStack;
class SkBaseDevice;
class SkBlitter;
class SkMatrix;
class SkMatrixProvider;
class SkPath;
class SkSurfaceProps;
class SkRegion;
class SkRasterClip;
struct SkRect;
class SkRRect;
class SkVertices;

// defaults to use SkBlitter::Choose()
class SkDraw : public SkDrawBase {
public:
    SkDraw();
    SkDraw(const SkDrawBase&);

    /* If dstOrNull is null, computes a dst by mapping the bitmap's bounds through the matrix. */
    void    drawBitmap(const SkBitmap&, const SkMatrix&, const SkRect* dstOrNull,
                       const SkSamplingOptions&, const SkPaint&) const override;
    void    drawSprite(const SkBitmap&, int x, int y, const SkPaint&) const;
    void    drawGlyphRunList(SkCanvas* canvas,
                             SkGlyphRunListPainterCPU* glyphPainter,
                             const sktext::GlyphRunList& glyphRunList,
                             const SkPaint& paint) const;

    void paintMasks(SkZip<const SkGlyph*, SkPoint> accepted, const SkPaint& paint) const override;

    void drawPoints(SkCanvas::PointMode, size_t count, const SkPoint[],
                       const SkPaint&, SkBaseDevice*) const;
    /* If skipColorXform, skips color conversion when assigning per-vertex colors */
    void drawVertices(const SkVertices*,
                      sk_sp<SkBlender>,
                      const SkPaint&,
                      bool skipColorXform) const;
    void drawAtlas(const SkRSXform[], const SkRect[], const SkColor[], int count,
                    sk_sp<SkBlender>, const SkPaint&);

#if defined(SK_SUPPORT_LEGACY_ALPHA_BITMAP_AS_COVERAGE)
    void drawDevMask(const SkMask& mask, const SkPaint&) const;
    void drawBitmapAsMask(const SkBitmap&, const SkSamplingOptions&, const SkPaint&) const;
#endif

private:
    void drawFixedVertices(const SkVertices* vertices,
                           sk_sp<SkBlender> blender,
                           const SkPaint& paint,
                           const SkMatrix& ctmInverse,
                           const SkPoint* dev2,
                           const SkPoint3* dev3,
                           SkArenaAlloc* outerAlloc,
                           bool skipColorXform) const;
};

#endif
