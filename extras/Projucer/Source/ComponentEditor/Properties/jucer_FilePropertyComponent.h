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
class FilePropertyComponent  : public PropertyComponent,
                               public FilenameComponentListener
{
public:
    FilePropertyComponent (const String& name,
                           const bool isDirectory,
                           const bool allowEditingOfFilename,
                           const String& fileBrowserWildcard = "*")
        : PropertyComponent (name),
          filenameComp (name, File(), allowEditingOfFilename,
                        isDirectory, false, fileBrowserWildcard,
                        String(), String())
    {
        addAndMakeVisible (filenameComp);
        filenameComp.addListener (this);
    }

    virtual void setFile (const File& newFile) = 0;
    virtual File getFile() const = 0;

    void refresh()
    {
        filenameComp.setCurrentFile (getFile(), false);
    }

    void filenameComponentChanged (FilenameComponent*)
    {
        if (getFile() != filenameComp.getCurrentFile())
            setFile (filenameComp.getCurrentFile());
    }

private:
    FilenameComponent filenameComp;
};
