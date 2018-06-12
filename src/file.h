/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/

#pragma once

namespace file
{
	static class ini
	{
	public:	
		ini() {};
		ini(const ini &right) 
		{
			fname = right.fname;
			strbuf = right.strbuf;
		};
		ini(const string filename)
		{
			fname.assign(filename);
			strbuf.clear();
		};

		static void clear() { return strbuf.clear(); };

		static bool read()
		{
			if (fname.empty()) return false;
			ifstream ifile = ifstream(fname);
			if (ifile.bad() || !ifile.is_open()) 
				return false;
			char buffer[MAX_PATH];
			while (!ifile.eof()) {
				ifile.getline(buffer, MAX_PATH);
				strbuf.push_back(buffer);
			} ifile.close();
			return true;
		};

		// writes data from the array "strbuf" to a file
		static bool write(const string filename)
		{
			if (filename.empty()) return false;
			ofstream ofile(filename, ios_base::out | ios_base::trunc);
			if (!ofile.is_open()) return false;
			for (size_t i = 0; i < strbuf.size(); i++)
				ofile << strbuf[i].c_str() << "\n";
			ofile.close();
			return true;
		};
		static bool write() { return write(fname); };

		// returns the parameter identifier starting with bgn_id
		static size_t find(string param, size_t bgn_id = 0)
		{
			for (size_t i = bgn_id; i < strbuf.size(); i++) {
				if (strbuf[i].find(param) != string::npos)
					return i;
			}
			return 0;
		};

		// returns a parameter string with the specified id
		static string get(size_t id)
		{
			if (!id || id >= strbuf.size()) return string();
			size_t pos = strbuf[id].find('=') + 1;
			if (pos == string::npos) return string();
			pos = strbuf[id].find_first_not_of(" \t", pos);

			return strbuf[id].substr(pos);
		};

		// returns full string by parameter
		static bool	get(string param, char *data)
		{
			for (size_t i = 0; i < strbuf.size(); i++) {
				string buf = strbuf[i];
				if (buf.find(param) != string::npos) {
					size_t pos = buf.find_first_of('=');
					if (pos == string::npos) continue;
					pos = buf.find_first_not_of("\t ", pos + 1);
					buf = buf.substr(pos);
					buf.copy(data, buf.find_first_of('\0'));
					return true;
				}
			} 
			return false;
		};

		// returns a value of type T
		template<typename T>
		static bool	get(string param, T &value)
		{
			size_t curr_id = 0;
			static size_t last_id;
			static string last;
			if (param == last)
				curr_id = find(param, last_id + 1);
			else curr_id = find(param);
			if (curr_id == 0) return false;
			last = param; last_id = curr_id;
			string buf = get(curr_id);
			if (buf.empty()) return false;
			
			return parse(buf, value);
		};

		// returns a list of values of type T
		template<typename ...Args> 
		static bool	get(string param, Args &...args)
		{
			size_t curr_id = 0;
			static size_t last_id;
			static string last;
			if (param == last)
				curr_id = find(param, last_id + 1);
			else curr_id = find(param);
			if (curr_id == 0) return false;
			last = param; last_id = curr_id;
			string buf = get(curr_id);
			if (buf.empty()) return false;

			return parse(buf, args...);
		};

		// changes the string in the array "strbuf" by the identifier
		static bool	set(size_t id, string str)
		{
			if (!id || id > strbuf.size()) return false;
			size_t pos = strbuf[id].find_first_of('=');
			if (pos == string::npos) return false;
			pos = strbuf[id].find_first_not_of("\t ", pos + 1);
			strbuf[id].replace(pos, strbuf[id].length(), str.c_str());
			return true;
		};

		// changes the string in the array "strbuf" by parameter name
		static bool set(string param, char *data)
		{
			size_t id = find(param);
			if (id == 0) return false;
			return set(id, data);
		};

		// changes value by parameter name
		template<typename T> 
		static bool set(string param, T value)
		{
			ostringstream stream;
			stream << setprecision(4) << value;
			return set(param, stream.str().data());
		};

		// add new string to array "strbuf" for writing to file later
		static void add(string param)
		{
			strbuf.push_back(param);
		};

		static void align(size_t columns_amount)
		{
			static size_t past_id = 0, offstr = 0;
			
			int32_t max_len = 0;
			for (size_t i = past_id; i < strbuf.size(); i++)
				max_len = max(max_len, (int32_t)strbuf[i].find('\t', offstr));
			
			for (size_t i = past_id; i < strbuf.size(); i++) {
				if (strbuf[i].front() == '#') continue;
				size_t pos = strbuf[i].find('\t', offstr);
				if (pos != string::npos) {
					size_t diff = (max_len - pos) + 1;
					size_t end = strbuf[i].find_first_not_of(" \t", pos);
					strbuf[i].replace(pos, end - pos, diff, ' ');
				}
			} offstr = max_len + 1;
			
			if (columns_amount <= 1) {
				past_id = strbuf.size();
				offstr = NULL;
			} else return align(--columns_amount);
		}

	protected:
		template<typename ...Args> 
		static bool parse(string &buf, Args &...args) { return true; };
		template<typename T, typename ...Args> 
		static bool	parse(string &buf, T &value, Args &...args)
		{	
			if (is_same<T, bool>())
				value = buf.find("1") != string::npos ? true : false;
			else if (is_class<T>() && is_same<T, string>()) {
				size_t pos = buf.find('\"');
				if (pos == string::npos) throw exception("ini file invalid argument");
				size_t end = buf.find_first_of('\"', pos + 1) - 1;
				value = reinterpret_cast<T &>(buf.substr(pos + 1, end - pos));
				buf.erase(pos, (end - pos) + 2);
			} else if (is_arithmetic<T>()) {
				if (is_floating_point<T>()) {
					if (is_same<T, long double>()) value = stold(buf);
					else if (is_same<T, double>()) value = stod(buf);
					else if (is_same<T, float>()) value = stof(buf);
				} else if (is_integral<T>()) {
					if (is_same<T, long long>()) value = stoull(buf);
					else if (is_same<T, long>()) value = stoul(buf);
					else if (is_same<T, char>()) value = stoi(buf);
					else if (is_same<T, short>())value = stoi(buf);
					else value = stoi(buf);
				}
			} else if (is_array<T>() || is_pointer<T>())
				return false;
			
			

			size_t pos = buf.find_first_of(" \t");
			if (pos != string::npos) {
				pos = buf.find_first_not_of(" \t", pos);
				buf.erase(0, pos);
			}
			return parse(buf, args...);
		};

	private:
		static string				fname;
		static vector<string>		strbuf;

	};
};
