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
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KNMUSICBACKENDGSTREAMERTHREAD_H
#define KNMUSICBACKENDGSTREAMERTHREAD_H

#include <gst/gst.h>

#include "knmusicglobal.h"

#include "knmusicstandardbackendthread.h"

/*
 * Oct 25th, 2015
 * There're something no one will tell you, I write it down here.
 * 1. Find a good example written in pure C.
 *         https://github.com/felipec/gst-player/blob/master/gst-backend.c
 *    This example helps me a lot on understanding GStreamer.
 * 2. The official tutorial has some error.
 *    The parameter of function gst_element_query_duration has been changed. In
 * the official tutorial, it's
 *         gst_element_query_duration (data.playbin2, &fmt, &data.duration)
 *    But now it should be
 *         gst_element_query_duration (data.playbin2, fmt, &data.duration)
 *    No more pointer needed.
 * 3. Not all formats audio will give out a DURATION_CHANGED message, but all of
 *    them will give out a GST_MESSAGE_NEW_CLOCK message.
 * 4. If you want to change volume of a playbin, set the volume property of the
 *    playbin.
 *
 * Oct 24th, 2015
 * There're playbin and playbin2 in GStreamer 0.10. But when it comes to 1.0
 * version of GStreamer, there will only be playbin. The new playbin is the
 * playbin2 in GStreamer 0.10.
 */

/*!
 * \brief The KNMusicBackendGStreamerThread class is the standard playing thread
 * for the GStreamer backend provided as official plugin.\n
 * It should only be used and constructed by KNMusicBackendGStreamer.
 */
class KNMusicBackendGStreamerThread : public KNMusicStandardBackendThread
{
    Q_OBJECT
public:
    /*!
     * \brief Construct KNMusicBackendGStreamerThread object.
     * \param parent The parent object.
     */
    explicit KNMusicBackendGStreamerThread(QObject *parent = 0);
    ~KNMusicBackendGStreamerThread();

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::loadFile().
     */
    bool loadFile(const QString &filePath) Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::reset().
     */
    void reset() Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::stop().
     */
    void stop() Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::play().
     */
    void play() Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::pause().
     */
    void pause() Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::volume().
     */
    int volume() Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::duration().
     * \return
     */
    qint64 duration() Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::position().
     */
    qint64 position() Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::state().
     */
    int state() const Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::setPlaySection().
     */
    void setPlaySection(const qint64 &start=-1,
                        const qint64 &duration=-1) Q_DECL_OVERRIDE;

    /*!
     * \brief Get the playbin of the playing thread. This function shouldn't be
     * called by any other class.
     * \return The playbin pointer.
     */
    GstElement *playbin();

signals:
    /*!
     * \brief This is a private signals. You Shouldn't use this signal.\n
     * This signal is used to process the event from the
     * \param bus The GstBut pointer.
     * \param message The message pointer, this is the thing we need.
     */
    void requireProcessEvent(int type);

public slots:
    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::save().
     */
    void save();

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::restore().
     */
    void restore(const QString &updatedFilePath=QString());

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::setVolume().
     */
    void setVolume(const int &volume) Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from KNMusicStandardBackendThread::setPosition().
     */
    void setPosition(const qint64 &position) Q_DECL_OVERRIDE;

    /*!
     * \brief This slot will be called from the call back function. It shouldn't
     * be called by other classes.
     */
    void updateDuration();

private slots:
    void onActionTick();
    void processEvents(int type);

private:
    static gboolean busWatch(GstBus *bus, GstMessage *message, gpointer data);
    inline void resetPipeline();
    inline void resetParameter();
    inline bool rebuildPipeline();
    inline void updateStartAndEndPosition();
    inline void setPlayingState(const int &state);
    QString m_filePath;
    qint64 m_startPosition,
           m_endPosition,
           m_duration,
           m_totalDuration;
    gint64 m_savedPosition;
    QTimer *m_tick;
    GstElement *m_playbin;
    const GstSeekFlags m_seekFlag;
    int m_state, m_volume;
    bool m_sectionSet;
};

#endif // KNMUSICBACKENDGSTREAMERTHREAD_H
