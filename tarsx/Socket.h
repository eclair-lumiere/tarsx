#pragma once
#include <string>
#include <netinet/in.h>

namespace tarsx {
	class Socket {
	public:
		Socket() = default;
		~Socket();

		auto init(int fd, bool owner, int domain) -> void;

		auto createSocket(int socketType = SOCK_STREAM, int domain = AF_INET) -> void;

		auto bind(const std::string& seraddr, int port) -> void;

		auto listen(int backlog) -> void;
		
		auto connect(const std::string& seraddr, uint16_t port) -> void;
		auto connect(sockaddr* seraddr, socklen_t addrlen) -> int;
		auto connectNoThrow(const std::string& seraddr, uint16_t port) -> int;

		auto accept(Socket& sock, sockaddr* sockaddr, socklen_t& socklen) -> int;

		auto fd() const { return fd_; }
		auto valid() const { return fd_ != -1; }
		auto close() -> void;

		auto parseAddr(const std::string& addr, in_addr& sinaddr) -> void;

		auto set_block(bool block) -> void;
		auto set_noCloseWait() -> void;
		auto set_closeWaitDefault() -> void;
		auto set_owner(bool owner) -> void { owner_ = owner; }

		auto recvfrom(void* buf, size_t len, std::string& fromAddr, uint16_t& fromPort, int flags = 0) -> int;
		static auto set_block(int fd, bool block) -> void;
	private:
		auto recvfrom(void* buf, size_t len, sockaddr* fromAddr, socklen_t& fromLen, int flags = 0) -> int;

	private:
		int fd_ = -1; /* INVALID_SOCKET = -1 */
		bool owner_ = true;
		int domain_ = AF_INET;
	};
}
