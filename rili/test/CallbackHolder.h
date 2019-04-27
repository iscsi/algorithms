#pragma once

/// @cond INTERNAL
namespace rili {
namespace test {

class UniversalCallbackHolder {
public:
	UniversalCallbackHolder() = default;
	virtual void const* getCallbackPointer() const = 0;
	virtual ~UniversalCallbackHolder() = default;

private:
	UniversalCallbackHolder(UniversalCallbackHolder const&) = delete;
	UniversalCallbackHolder& operator=(UniversalCallbackHolder const&) = delete;
};

template <typename CallbackType>
class CallbackHolder : public UniversalCallbackHolder {
public:
	explicit CallbackHolder(CallbackType const& cb) : UniversalCallbackHolder(), m_cb(cb) {}
	void const* getCallbackPointer() const override { return &m_cb; }
	virtual ~CallbackHolder() = default;

private:
	CallbackHolder() = delete;
	CallbackHolder(CallbackHolder const&) = delete;
	CallbackHolder& operator=(CallbackHolder const&) = delete;

private:
	CallbackType m_cb;
};

}  // namespace test
}  // namespace rili
/// @endcond INTERNAL
