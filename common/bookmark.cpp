/**
 * Copyright (C) 2013, Pelagicore
 *
 * Author: Marcel Schuette <marcel.schuette@pelagicore.com>
 *
 * This file is part of the GENIVI project Browser Proof-Of-Concept
 * For further information, see http://genivi.org/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "bookmark.h"

Bookmark::Bookmark(QObject *parent) :
    QObject(parent), i32Uid(0)
  , i32Type(0)
  , strParentFolderPath("")
  , strTitle("")
  , strUrl("")
  , strIconPath("")
  , strThumbnailPath("")
{
}
