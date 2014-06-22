#include "cleventlist.h"

#include "clerrorchecking.h"
#include "error.h"

QVector<cl_event> eventVector(const ClEventList& events) {
    QVector<cl_event> vec;
    foreach (ClEvent e, events)
        vec << e.get();
    return vec;
}

void waitForAll(Error& error, const ClEventList& events) {
    QVector<cl_event> vec(eventVector(events));
    cl_int status = clWaitForEvents(vec.size(), vec.data());
    clCheckStatus(error, status, "clWaitForEvents");
}

void checkStatusComplete(Error& error, const ClEventList& events) {
    foreach (const ClEvent& e, events) {
        e.checkStatusComplete(error);
        if (error) return;
    }
}
