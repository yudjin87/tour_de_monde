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

#ifndef IPERSISTENCEDELEGATE_H
#define IPERSISTENCEDELEGATE_H

#include <components/persistence/persistence_global.h>

#include <QtCore/QObject>
#include <QtCore/QList>

class IComponent;
class IServiceLocator;
class QByteArray;

/*!
 * @brief
 */
class PERSISTENCE_API IPersistenceDelegate : public QObject
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{IPersistenceDelegate}.
     */
    IPersistenceDelegate(){}

    virtual void save(IServiceLocator *locator, const QList<IComponent *> &components, QByteArray &saveStream) = 0;
    virtual void load(IServiceLocator *locator, const QList<IComponent *> &components,  const QByteArray &loadStream) = 0;

private:
    Q_DISABLE_COPY(IPersistenceDelegate)
};

#endif // IPERSISTENCEDELEGATE_H
