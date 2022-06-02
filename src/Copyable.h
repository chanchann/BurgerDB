#ifndef BURGERDB_COPYABLE_H_
#define BURGERDB_COPYABLE_H_

namespace burgerdb {

class Copyable {
protected:
    Copyable() = default;
    ~Copyable() = default;
};

} // namespace burgerdb

#endif  // BURGERDB_COPYABLE_H_