/*
 * Copyright (C) Kreogist Dev Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KNMUSICHEADERPLAYERBASE_H
#define KNMUSICHEADERPLAYERBASE_H

#include "knmusicplayerbase.h"

/*!
 * \brief The KNMusicHeaderPlayerBase class provided a basic interface for all
 * the header player.
 */
class KNMusicHeaderPlayerBase : public KNMusicPlayerBase
{
    Q_OBJECT
public:
    /*!
     * \brief Construct a KNMusicHeaderPlayerBase widget.
     * \param parent The parent widget.
     */
    KNMusicHeaderPlayerBase(QWidget *parent = 0) : KNMusicPlayerBase(parent){}

    /*!
     * \brief Get the lyrics widget which is provided by the header player.
     * \return The lyrics widget pointer of the header player.
     */
    virtual QWidget *lyrics()=0;

signals:
    /*!
     * \brief This signal is asked the main window to show up the main player
     * widget.
     */
    void requireShowMainPlayer();

    /*!
     * \brief This signal is used to ask to hide the main window, and show the
     * mini player.
     */
    void requireShowMiniPlayer();

    /*!
     * \brief This signal is used to ask the mouse sense header to check the
     * cursor position to activate or inactivate the content of header player.
     */
    void requireCheckCursor();

public slots:
    /*!
     * \brief When the mouse entered, activate function should be called by the
     * header.
     */
    virtual void activate()=0;

    /*!
     * \brief When the mouse leaved, inactivate function should be called by the
     * header.
     */
    virtual void inactivate()=0;

    /*!
     * \brief Load configure data to the header player.
     */
    virtual void loadConfigure()=0;

    /*!
     * \brief Save header player settings to configure data.
     */
    virtual void saveConfigure()=0;

    /*!
     * \brief Reset the header player.
     */
    virtual void reset()=0;
};

#endif // KNMUSICHEADERPLAYERBASE_H
