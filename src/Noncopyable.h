#ifndef BURGERDB_NONCOPYABLE_H_
#define BURGERDB_NONCOPYABLE_H_

namespace burgerdb {

class Noncopyable
{
public:
    Noncopyable(const Noncopyable&) = delete;
    void operator=(const Noncopyable&) = delete;

protected:
    Noncopyable() = default;
    ~Noncopyable() = default;
};

} // namespace burgerdb

#endif  // BURGERDB_NONCOPYABLE_H_