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

#ifndef IFEATUREDATASET_H
#define IFEATUREDATASET_H

#include "IGeoDataset.h"

#include <QtCore/QList>

class IFeatureClass;

// shp + shx + dbf = dataset (for shapes)
class GEODATABASE_API IFeatureDataset : public IGeoDataset
{
    Q_OBJECT
    Q_PROPERTY(QList<IFeatureClass *> classes READ classes)
public:
    IFeatureDataset(){}

    virtual QList<IFeatureClass *> classes() = 0;

public slots:
    virtual IFeatureClass* classById(int id) = 0;
    virtual IFeatureClass* classByName(const QString &className = "") = 0;

private:
    Q_DISABLE_COPY(IFeatureDataset)
};

#endif // IFEATUREDATASET_H
