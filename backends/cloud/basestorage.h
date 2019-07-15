/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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
 *
 */

#ifndef BACKENDS_CLOUD_BASE_STORAGE_H
#define BACKENDS_CLOUD_BASE_STORAGE_H

#include "backends/cloud/storage.h"
#include "backends/networking/curl/curljsonrequest.h"

namespace Cloud {

class BaseStorage: public Cloud::Storage {
protected:
	/** Storage's access and refresh tokens. */
	Common::String _token, _refreshToken;

	/**
	 * Gets token from cloud.scummvm.org using given code.
	 * Base implementation for storages with common auth procedure.
	 */
	virtual void getAccessToken(Common::String code);

	/**
	 * Handles JSON response which should contain access token requested 
	 * with getAccessToken().
	 */
	virtual void codeFlowComplete(Networking::JsonResponse response);

	/**
	 * Handles network errors occurred while getting access token requested
	 * with getAccessToken().
	 */
	virtual void codeFlowFailed(Networking::ErrorResponse error);

	/**
	 * Return cloud provider name, used in cloud.scummvm.org endpoints.
	 * @return cloud provider (for example, "dropbox").
	 */
	virtual Common::String cloudProvider() = 0;

	/**
	 * Return CloudManager's StorageID for this storage.
	 * @return StorageID corresponding to this storage (for example,
	 *         kStorageDropboxId).
	 */
	virtual uint32 storageIndex() = 0;

public:
	BaseStorage();
	BaseStorage(Common::String token, Common::String refreshToken);
	virtual ~BaseStorage();
};

} // End of namespace Cloud

#endif