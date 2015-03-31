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

#include <geometry/geometry_api.h>
#include <geometry/GeometryType.h>

#include <QtCore/QObject>
#include <QtCore/QRectF>

class GEOMETRY_API AbstractGeometry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Geometry::Type type READ type)
    Q_PROPERTY(QRectF extent READ extent)
public:
    explicit AbstractGeometry(QObject *parent = nullptr);
    explicit AbstractGeometry(const QRectF &extent, QObject *parent = nullptr);
    virtual ~AbstractGeometry();

    virtual Geometry::Type type() const = 0;

    const QRectF &extent() const;

protected:
    void setExtent(const QRectF &extent);

private:
    QRectF m_extent;
};
