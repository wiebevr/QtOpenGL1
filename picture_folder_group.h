#ifndef PICTURE_FOLDER_GROUP_H
#define PICTURE_FOLDER_GROUP_H

#include <QDir>
#include <QString>

#include "object_group.h"

class PictureFolderGroup
    : public ObjectGroup
{
    Q_OBJECT

    public:
        PictureFolderGroup(QString folder, QObject *parent = 0);
        ~PictureFolderGroup();


    private:
        QDir _directory;






};
#endif // PICTURE_FOLDER_GROUP_H
