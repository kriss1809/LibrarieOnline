#include <string>

using namespace std;

class DTO
{
private:
	string gen;
	int cnt;
public:
	DTO() = default;
	DTO(const string g, int c) :gen{ g }, cnt{ c } {};

	string get_gen() const
	{
		return this->gen;
	}

	int get_cnt() const noexcept
	{
		return this->cnt;
	}

	void increment_cnt() noexcept
	{
		cnt++;
	}
};