/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
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

#pragma once

#include <geometry/AbstractGeometry.h>

class GEOMETRY_API Point : public AbstractGeometry
{
    Q_OBJECT
public:
    explicit Point(QObject *parent = nullptr);
    explicit Point(const qreal x, const qreal y, QObject *parent = nullptr);

    qreal x() const {return m_x;}
    qreal y() const {return m_y;}

    void setX(const qreal x) {m_x = x;}
    void setY(const qreal y) {m_y = y;}

    void putCoords(const qreal x, const qreal y);

    Geometry::Type type() const override;

private:
    qreal m_x;
    qreal m_y;
};
