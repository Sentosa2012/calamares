/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "UnpackFSJob.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QFile>
#include <QFileInfo>

UnpackFSJob::UnpackFSJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}


UnpackFSJob::~UnpackFSJob() {}


QString
UnpackFSJob::prettyName() const
{
    return tr( "Filling up filesystems." );
}

Calamares::JobResult
UnpackFSJob::exec()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !gs->contains( "rootMountPoint" ) )
    {
        cError() << "No mount point for root partition.";
        return Calamares::JobResult::internalError(
            tr( "No mount point for root partition" ),
            tr( "globalstorage does not contain a \"rootMountPoint\" key, doing nothing" ),
            0 );
    }

    QString s = gs->value( "rootMountPoint" ).toString();
    if ( s.isEmpty() || !QFile::exists( s ) || !QFileInfo( s ).isDir() )
    {
        cError() << "Bad root mount point" << s;
        return Calamares::JobResult::error(
            tr( "Bad mount point for root partition" ),
            tr( "rootMountPoint is \"%1\", which does not exist, doing nothing" ).arg( s ) );
    }

    return Calamares::JobResult::internalError( "UnpackFS", "Unimplemented", 0 );  //Calamares::JobResult::);
}


void
UnpackFSJob::setConfigurationMap( const QVariantMap& map )
{
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( UnpackFSJobFactory, registerPlugin< UnpackFSJob >(); )