/*
 * Copyright (c) 2022, suncloudsmoon and the Auto-Store contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef AUTOSTORE_HPP
#define AUTOSTORE_HPP

#include <string>
#include <fstream>
#include <ostream>
#include <istream>
#include <functional>

/*
* Item must be copyable, movable, and define operator(s) [<<, >>]
*/
namespace au {
	constexpr const char* rand_func_file_extension{ ".txt" };
	template<typename T>
	class auto_store {
	public:
		auto_store(const T& store_value, const std::string& dest_path) : file_path(dest_path) {
			std::ifstream in(file_path);
			if (in.is_open())
				in >> value;
			else
				value = store_value;
		}
		auto_store(T&& store_value, const std::string& dest_path) : file_path(dest_path) {
			std::ifstream in(file_path);
			if (in.is_open())
				in >> value;
			else
				value = store_value;
		}
		auto_store(const T& store_value, std::function<unsigned long()> rand_func,
					const std::string& initial_name = "") {
			file_path = initial_name + "_" + std::to_string(rand_func()) + rand_func_file_extension;
			std::ifstream in(file_path);
			if (in.is_open())
				in >> value;
			else
				value = store_value;
		}
		auto_store(T&& store_value, std::function<unsigned long()> rand_func, 
					const std::string& initial_name = "") {
			file_path = initial_name + "_" + std::to_string(rand_func()) + rand_func_file_extension;
			std::ifstream in(file_path);
			if (in.is_open())
				in >> value;
			else
				value = store_value;
		}
		~auto_store() {
			std::ofstream out(file_path);
			if (out.is_open())
				out << value;
		}

		void set_value(const T& value) {
			this->value = value;
		}
		void set_value(T&& value) noexcept {
			this->value = value;
		}

		const T& get_value() const noexcept {
			return value;
		}
		const std::string& get_file_path() const noexcept {
			return file_path;
		}

		T& operator*() {
			return value;
		}

		void operator=(const T& store_value) {
			set_value(store_value);
		}

		void operator=(T&& store_value) noexcept {
			set_value(store_value);
		}

		friend std::ostream& operator<<(std::ostream& out, const auto_store<T> &st) {
			out << st.value;
			return out;
		}
		friend std::istream& operator>>(std::istream& in, auto_store<T>& st) {
			in >> st.value;
			return in;
		}
	private:
		T value;
		std::string file_path;
	};
}

#endif /* AUTOSTORE_HPP */