#include "picture_folder_group.h"
#include "display_plane.h"

#include <QStringList>

PictureFolderGroup::PictureFolderGroup(QString folder, QObject *parent)
    : ObjectGroup(parent)
{
    QStringList filters;
    QStringList pictureNames;
    filters 
        << "*.jpg"
        << "*.JPG"
        << "*.jpeg"
        << "*.JPEG"
        << "*.bmp"
        << "*.BMP"
        << "*.png"
        << "*.PNG"
        << "*.gif"
        << "*.GIF"
        << "*.tiff"
        << "*.TIFF";
    _directory.cd(folder);
    _directory.setNameFilters(filters);
    pictureNames = _directory.entryList();
    
    if (pictureNames.size() < 1)
        qDebug() << "No images found.";
    
    for (int i = 0; i < pictureNames.size(); ++i)
    {
        addObject(new DisplayPlane(_directory.filePath(
                        pictureNames[i]), this)); 
        qDebug() << pictureNames[i];
    }
}

PictureFolderGroup::~PictureFolderGroup()
{

}

