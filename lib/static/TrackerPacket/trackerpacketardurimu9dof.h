#ifndef TRACKERPACKETARDURIMU9DOF_H
#define TRACKERPACKETARDURIMU9DOF_H

#include <itrackerpacket.h>
#include <bytearrayconversion.h>

#include <QtCore>
#include <QByteArray>
#include <QVector3D>

class TrackerPacketArdurImu9Dof : public ITrackerPacket
{

    public:
        TrackerPacketArdurImu9Dof( QByteArray bytes );

        // ITrackerPacket interface
    protected:
        void fromBytes(QByteArray bytes);
};

#endif // TRACKERPACKETARDURIMU9DOF_H
