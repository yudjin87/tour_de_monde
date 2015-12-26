/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "SimpleLineSymbol.h"
#include "display/ISymbolVisitor.h"

#include <geometry/Polyline.h>
#include <geometry/Point.h>
#include <geometry/Path.h>

#include <QtGui/QPainter>

SimpleLineSymbol::SimpleLineSymbol(QObject *parent)
    : LineSymbol(parent)
    , m_pen()
    , m_oldPen()
{
    m_pen.setCosmetic(true);
}

SymbolType SimpleLineSymbol::type() const
{
    return SymbolType::SimpleLineSymbol;
}

void SimpleLineSymbol::accept(ISymbolVisitor &visitor)
{
    visitor.visit(*this);
}

SimpleLineSymbol::SimpleLineSymbol(const SimpleLineSymbol &o, QObject *parent)
    : LineSymbol(o, parent)
    , m_pen(o.m_pen)
    , m_oldPen(o.m_oldPen)
{
    m_pen.setCosmetic(true);
}

ISymbol* SimpleLineSymbol::clone(QObject* parent) const
{
    return new SimpleLineSymbol(*this, parent);
}

void SimpleLineSymbol::setupTourDuMonde(QPainter *painter)
{
    m_pen.setColor(color());
    m_pen.setWidthF(width());

    m_oldPen = painter->pen();
    painter->setPen(m_pen);
}

void SimpleLineSymbol::resetTourDuMonde(QPainter *painter)
{
    painter->setPen(m_oldPen);
}

Qt::PenStyle SimpleLineSymbol::style() const
{
    return m_pen.style();
}

void SimpleLineSymbol::setStyle(Qt::PenStyle style)
{
    m_pen.setStyle(style);
}

void SimpleLineSymbol::drawPolyline(const Polyline &polyline, QPainter &painter)
{
    for (const Path *path : polyline.paths())
    {
        QPolygonF poly;
        for (const Point *point: path->points())
        {
            poly.push_back(QPointF(point->x(), point->y()));
        }
        painter.drawPolyline(poly);
    }
}

