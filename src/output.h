/*************************************************************************************
 *  Copyright (C) 2012 by Alejandro Fiestas Olivares <afiestas@kde.org>              *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU General Public License                      *
 *  as published by the Free Software Foundation; either version 2                   *
 *  of the License, or (at your option) any later version.                           *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
 *************************************************************************************/

#ifndef OUTPUT_H
#define OUTPUT_H

#include "kscreen_export.h"
#include "mode.h"

#include <QtCore/QObject>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtCore/QHash>
#include <QtCore/QMetaType>

class Mode;
class KSCREEN_EXPORT Output : public QObject
{
    Q_OBJECT

    public:
        Q_PROPERTY(int id READ id WRITE setId NOTIFY outputChanged)
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY outputChanged)
        Q_PROPERTY(QString type READ type WRITE setType NOTIFY outputChanged)
        Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY outputChanged)
        Q_PROPERTY(ModeList modes READ modes CONSTANT)
        Q_PROPERTY(QPoint pos READ pos WRITE setPos NOTIFY posChanged)
        Q_PROPERTY(Rotation rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
        Q_PROPERTY(int currentMode READ currentMode WRITE setCurrentMode NOTIFY currentModeChanged)
        Q_PROPERTY(bool connected READ isConnected WRITE setConnected NOTIFY isConnectedChanged)
        Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY isEnabledChanged)
        Q_PROPERTY(bool primary READ isPrimary WRITE setPrimary NOTIFY isPrimaryChanged)
        Q_PROPERTY(QList<int> clones READ clones WRITE setClones NOTIFY clonesChanged)

        Q_ENUMS(Rotation)

        enum Rotation {
            None = 1,
            Right = 2,
            Inverted = 4,
            Left = 8
        };

	explicit Output();
        explicit Output(int id, QObject* parent = 0);
        virtual ~Output();

	int id() const;
	void setId(int id);

        QString name() const;
        void setName(const QString& name);

        QString type() const;
        void setType(const QString& type);

        QString icon() const;
        void setIcon(const QString& icon);

        Q_INVOKABLE Mode* mode(int id) const;
        QHash<int, Mode*> modes() const;
        void setModes(ModeList modes);

        int currentMode() const;
        void setCurrentMode(int mode);

        QPoint pos() const;
        void setPos(const QPoint& pos);

        Rotation rotation() const;
        void setRotation(Rotation rotation);

        bool isConnected() const;
        void setConnected(bool connected);

        bool isEnabled() const;
        void setEnabled(bool enabled);

        bool isPrimary() const;
        void setPrimary(bool primary);

        QList<int> clones();
        void setClones(QList<int> outputlist);

    Q_SIGNALS:
	void outputChanged();
	void posChanged();
	void currentModeChanged();
	void rotationChanged();
	void isConnectedChanged();
	void isEnabledChanged();
	void isPrimaryChanged();
	void clonesChanged();

    private:
        int m_id;
        QString m_name;
        QString m_type;
        QString m_icon;
        ModeList m_modeList;
        QList<int> m_clones;
        int m_currentMode;
        QSize m_size;
        QPoint m_pos;
        Rotation m_rotation;
        bool m_connected;
        bool m_enabled;
        bool m_primary;
};

typedef QHash<int, Output*> OutputList;
Q_DECLARE_METATYPE(OutputList);

#endif //OUTPUT_H
