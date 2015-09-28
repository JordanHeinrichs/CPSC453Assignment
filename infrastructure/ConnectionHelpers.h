#pragma once

#define safeConnect(sender, signal, receiver, method) \
{ \
    const bool successful = connect(dynamic_cast<QObject*>(&*sender), signal, dynamic_cast<QObject*>(&*receiver), method); \
    Q_ASSERT(successful); \
}
