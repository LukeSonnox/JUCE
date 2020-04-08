/*
  ==============================================================================

   This file is part of the JUCE 6 technical preview.
   Copyright (c) 2017 - ROLI Ltd.

   You may use this code under the terms of the GPL v3
   (see www.gnu.org/licenses).

   For this technical preview, this file is not subject to commercial licensing.

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#pragma once


//==============================================================================
class VersionInfo
{
public:
    struct Asset
    {
        const String name;
        const String url;
    };

    static std::unique_ptr<VersionInfo> fetchFromUpdateServer (const String& versionString);
    static std::unique_ptr<VersionInfo> fetchLatestFromUpdateServer();
    static std::unique_ptr<InputStream> createInputStreamForAsset (const Asset& asset, int& statusCode);

    bool isNewerVersionThanCurrent();

    const String versionString;
    const String releaseNotes;
    const std::vector<Asset> assets;

private:
    VersionInfo() = default;

    static std::unique_ptr<VersionInfo> fetch (const String&);
};
