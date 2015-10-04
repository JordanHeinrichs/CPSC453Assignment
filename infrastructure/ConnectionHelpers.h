#pragma once

#define safeConnect(sender, signal, receiver, method) \
{ \
    const bool successful = connect(dynamic_cast<QObject*>(&*sender), signal, dynamic_cast<QObject*>(&*receiver), method); \
    Q_ASSERT(successful); \
}

// With connection type, it is not correct to assert the connection since for
// unique connections it would return false if already connected.
#define safeConnectUnique(sender, signal, receiver, method) \
{ \
    connect(dynamic_cast<QObject*>(&*sender), signal, dynamic_cast<QObject*>(&*receiver), method, Qt::UniqueConnection); \
}

#define safeDisconnect(sender, signal, receiver, method) \
{ \
    disconnect(dynamic_cast<QObject*>(&*sender), signal, dynamic_cast<QObject*>(&*receiver), method); \
}
