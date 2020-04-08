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

#include "jucer_FillType.h"

//==============================================================================
class StrokeType
{
public:
    StrokeType()  : stroke (1.0f)
    {
        reset();
    }

    String getPathStrokeCode() const
    {
        PathStrokeType defaultStroke (1.0f);

        String s;

        s << "PathStrokeType (" << CodeHelpers::floatLiteral (stroke.getStrokeThickness(), 3);

        if (stroke.getJointStyle() != defaultStroke.getJointStyle()
            || stroke.getEndStyle() != defaultStroke.getEndStyle())
        {
            s << ", ";

            switch (stroke.getJointStyle())
            {
                case PathStrokeType::mitered:   s << "PathStrokeType::mitered"; break;
                case PathStrokeType::curved:    s << "PathStrokeType::curved"; break;
                case PathStrokeType::beveled:   s << "PathStrokeType::beveled"; break;
                default:                        jassertfalse; break;
            }

            if (stroke.getEndStyle() != defaultStroke.getEndStyle())
            {
                s << ", ";

                switch (stroke.getEndStyle())
                {
                    case PathStrokeType::butt:      s << "PathStrokeType::butt"; break;
                    case PathStrokeType::square:    s << "PathStrokeType::square"; break;
                    case PathStrokeType::rounded:   s << "PathStrokeType::rounded"; break;
                    default:                        jassertfalse; break;
                }
            }
        }

        s << ")";
        return s;
    }

    String toString() const
    {
        String s;
        s << stroke.getStrokeThickness();

        switch (stroke.getJointStyle())
        {
            case PathStrokeType::mitered:   s << ", mitered"; break;
            case PathStrokeType::curved:    s << ", curved"; break;
            case PathStrokeType::beveled:   s << ", beveled"; break;
            default:                        jassertfalse; break;
        }

        switch (stroke.getEndStyle())
        {
            case PathStrokeType::butt:      s << ", butt"; break;
            case PathStrokeType::square:    s << ", square"; break;
            case PathStrokeType::rounded:   s << ", rounded"; break;
            default:                        jassertfalse; break;
        }

        return s;
    }

    void restoreFromString (const String& s)
    {
        reset();

        if (s.isNotEmpty())
        {
            const float thickness = (float) s.upToFirstOccurrenceOf (",", false, false).getDoubleValue();

            PathStrokeType::JointStyle joint = stroke.getJointStyle();

            if (s.containsIgnoreCase ("miter"))         joint = PathStrokeType::mitered;
            else if (s.containsIgnoreCase ("curve"))    joint = PathStrokeType::curved;
            else if (s.containsIgnoreCase ("bevel"))    joint = PathStrokeType::beveled;

            PathStrokeType::EndCapStyle end = stroke.getEndStyle();

            if (s.containsIgnoreCase ("butt"))          end = PathStrokeType::butt;
            else if (s.containsIgnoreCase ("square"))   end = PathStrokeType::square;
            else if (s.containsIgnoreCase ("round"))    end = PathStrokeType::rounded;

            stroke = PathStrokeType (thickness, joint, end);
        }
    }

    bool isOpaque() const
    {
        return fill.isOpaque();
    }

    bool isInvisible() const
    {
        return fill.isInvisible() || stroke.getStrokeThickness() <= 0.0f;
    }

    bool operator== (const StrokeType& other) const noexcept
    {
        return stroke == other.stroke && fill == other.fill;
    }

    bool operator!= (const StrokeType& other) const noexcept
    {
        return ! operator== (other);
    }

    //==============================================================================
    PathStrokeType stroke;
    JucerFillType fill;

private:
    void reset()
    {
        stroke = PathStrokeType (5.0f);
        fill = JucerFillType();
        fill.colour = Colours::black;
    }
};
