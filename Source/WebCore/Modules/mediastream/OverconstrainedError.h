/*
 * Copyright (C) 2016 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(MEDIA_STREAM)

#include "MediaConstraintType.h"
#include <wtf/RefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class OverconstrainedError  : public RefCounted<OverconstrainedError> {
public:
    static Ref<OverconstrainedError> create(const String& constraint, const String& message)
    {
        return adoptRef(*new OverconstrainedError(constraint, message));
    }
    static Ref<OverconstrainedError> create(MediaConstraintType invalidConstraint, const String& message)
    {
        return adoptRef(*new OverconstrainedError(invalidConstraint, message));
    }

    String constraint() const;
    String message() const { return m_message; }
    String name() const { return "OverconstrainedError"_s; }

protected:
    OverconstrainedError(const String& constraint, const String& message)
        : m_constraint(constraint)
        , m_message(message)
    {
    }
    OverconstrainedError(MediaConstraintType invalidConstraint, const String& message)
        : m_invalidConstraint(invalidConstraint)
        , m_message(message)
    {
    }

private:
    mutable String m_constraint;
    MediaConstraintType m_invalidConstraint;
    String m_message;
};

inline String OverconstrainedError::constraint() const
{
    if (m_constraint.isNull())
        m_constraint = convertToString(m_invalidConstraint);
    return m_constraint;
}

} // namespace WebCore

#endif
