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
Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KNMUSICSTOREERRORDIMMER_H
#define KNMUSICSTOREERRORDIMMER_H

#include <QWidget>

class QTimeLine;
/*!
 * \brief The KNMusicStoreErrorDimmer class is designed to be used as two ways.
 * First, it will be used as the shadow widget for the content, second, it will
 * display the error information.\n
 * The show and hide of the widget will be animation in and out. The icon will
 * be only one error icon, and the button will be only retry and okay. The retry
 * button could be hidden.
 */
class KNMusicStoreErrorDimmer : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Construc a KNMusicStoreErrorDimmer widget.
     * \param parent The parent widget.
     */
    explicit KNMusicStoreErrorDimmer(QWidget *parent = 0);

signals:

public slots:
    /*!
     * \brief Start to show the dimmer. This dimmer won't show any text or the
     * control widgets at the end.
     */
    void showDimmer();

    /*!
     * \brief Show the error dimmer, but display the set text.
     */
    void showErrorDimmer();

    /*!
     * \brief Hide the dimmer. All the text will be hidden first, and the dimmer
     * will fade out and hide the widget.
     */
    void hideDimmer();

private slots:
    void onThemeChanged();
    void onTimeLineFinish();
    void onBackgroundAlphaChange(int frame);

private:
    inline void startAnime(int endFrame);
    QTimeLine *m_background;
    bool m_showLabel;
};

#endif // KNMUSICSTOREERRORDIMMER_H