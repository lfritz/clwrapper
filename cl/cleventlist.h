#pragma once

#include <QList>
#include <QVector>

#include "clevent.h"

typedef QList<ClEvent> ClEventList;

// Get cl_event objects.
QVector<cl_event> eventVector(const ClEventList& events);

// Wait for all events.
void waitForAll(Error& error, const ClEventList& events);

// Check that all commands completed properly; raise an error if they didn't.
void checkStatusComplete(Error& error, const ClEventList& events);
