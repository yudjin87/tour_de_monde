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

#ifndef LAYER_H
#define LAYER_H

#include "carto_api.h"

#include <QtCore/QString>
#include <QtCore/QRectF>

class IDisplay;

class CARTO_API AbstractLayer
{
public:
    AbstractLayer();
    virtual ~AbstractLayer();

    virtual void draw(IDisplay *display) = 0;

    virtual QRectF extent() const = 0;

    const QString &name() const;
    void setName(const QString &name);

    bool isVisible() const;
    void setVisible(bool visible = true);

    double minimumScale() const;
    double maximumScale() const;

    void setMinimumScale(double minimumScale);
    void setMaximumScale(double maximumScale);

protected:
    virtual void hide() = 0;
    virtual void show() = 0;

private:
    QString m_name;
    bool m_isVisible;
    double m_minimumScale;
    double m_maximumScale;
};

#endif // LAYER_H
