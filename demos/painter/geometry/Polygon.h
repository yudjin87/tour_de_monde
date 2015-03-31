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

#include <geometry/Polycurve.h>
#include <QtCore/QVector>

class Ring;
typedef QVector<Ring *> RingList;

class GEOMETRY_API Polygon : public Polycurve
{
    Q_OBJECT
public:
    explicit Polygon(QObject *parent = nullptr);
    explicit Polygon(int size, QObject *parent = nullptr);
    explicit Polygon(const QRectF &extent, QObject *parent = nullptr);
    explicit Polygon(std::initializer_list<QPointF> points, QObject *parent = nullptr);

    ~Polygon();

    RingList &rings();
    const RingList &rings() const;

    Geometry::Type type() const override;

private:
    RingList m_rings;
};
