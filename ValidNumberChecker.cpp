#include <string>
#include <iostream>

//Getting rid of spaces
std::string stripSpaces(const std::string & str)
{
	std::string result = "";
	for (auto i : str)
	{
		//checking of empty spaces in the string
		if (i != ' ')
		{
			result += i;
		}
	}
	return result;
}

//checking for space in between numbers
bool SpaceChecker(std::string str)
{
	//checking if there is space in between symbols
	bool spaceSwtich = false;
	//iterating the string looking for empty spaces
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == ' ')
		{
			if (i > 0)
			{
				//checking if there a number before a space
				if ((str[i - 1] >= 48 && str[i - 1] <= 57) || str[i-1] == 'e' || str[i-1] == '.' || str[i-1] == '-' || str[i-1] == '+')
				{
					//active the switch
					spaceSwtich = true;
				}
			}

			//if there is a number or symbol in between spaces
			if (spaceSwtich)
			{
				//if this is not the last number
				if (i + 1 < str.size())
				{
					//if there is a number or symbol after a space
					if ((str[i + 1] >= 48 && str[i + 1] <= 57) || str[i+1] == 'e' || str[i+1] == '.' || str[i+1] == '-' || str[i+1] == '+')
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

//checking to see if the number is there 
bool isNumeric(std::string s, std::string integer_or_double)
{
	//creating a string with no spaces to make it easier to analyze
	std::string subset = stripSpaces(s);
	
	//checking if the symbols are last
	if (subset.find('+') == subset.size() - 1 || subset.find('-') == subset.size() - 1 || subset.find('e') == subset.size() - 1)
	{
		return false;
	}

	/************making sure that the symbols are not all the way at the end *******************/
	//if . is the end making sure that it has a number in front of it
	if (subset.find('.') == subset.size() - 1)
	{
		if (!(subset[subset.find('.') - 1] >= 48 && subset[subset.find('.') - 1] <= 57))
		{
			return false;
		}
	}

	//if all were spaces the string would be empty
	if (subset.size() == 0)
	{
		return false;
	}

	//if there is just one element after eliminating spaces
	//fast base case
	else if (subset.size() == 1)
	{
		if (!(subset[0] >= 48 && subset[0] <= 57))
		{
			return false;
		}

		//if it is just one element and it is a number
		else
		{
			return true;
		}
	}
	
	
	//checking if there are double e. They can never be double e
	if (subset.find('e', subset.find('e') + 1) != -1)
	{	
		return false;
	}

	//if there is double - or + there should be an e in between
	if (subset.find('-', subset.find('-') + 1) != -1 || subset.find('+', subset.find('+') + 1) != -1 || subset.find('.', subset.find('.') + 1) != -1)
	{
		//if there are double minus an e should be in front of the second minus
		if (subset.find('-', subset.find('-') + 1) != -1)
		{
			if (subset[subset.find('-', subset.find('-') + 1) - 1] != 'e')
			{
				return false;
			}
		}

		//if there are double plus an e should be in front of the second minus
		if (subset.find('+', subset.find('+') + 1) != -1)
		{
			if (subset[subset.find('+', subset.find('+') + 1) - 1] != 'e')
			{
				return false;
			}
		}

		//if there are double dot an e should be in front of the second minus
		if (subset.find('.', subset.find('.') + 1) != -1)
		{
			if (subset[subset.find('.', subset.find('.') + 1) - 1] != 'e')
			{
				return false;
			}
		}

		
		//if there are 3 elements and 2 of them are double symbols then it could not be a valid number e.g -e-
		if (subset.size() == 3)
		{
			return false;
		}
	}
	
	//after striping the string out of spaces, checking all the cases. Iterate through every character of the string
	for (size_t i = 0; i < subset.size(); ++i)
	{
		//if the char is a symbol
		if (subset[i] == 'e' || subset[i] == '.' || subset[i] == '-' || subset[i] == '+' || (subset[i] >= 48 && subset[i] <= 57))
		{
			if (subset[i] == 'e' || subset[i] == '-' || subset[i] == '.' || subset[i] == '+')
			{
				//check if these are the last ones
				if (subset[i] == 'e' || subset[i] == '-' || subset[i] == '+')
				{
					if (s[i+1] == '\0')
					{
						return false;
					}
				}

				if (subset[i] == 'e')
				{
					//e as the first one is not allowed
					if (i == 0)
					{
						return false;
					}

					if (i + 1 < subset.size())
					{

						//if there is a dot after e
						if (subset.find('.', i + 1) != -1)
						{
							return false;
						}
						//if there is a negative sign after e
						if (subset[i + 1] == '-')
						{
							//if there is nothing after the negative sign is wrong input
							if (i + 2 == subset.size())
							{
								return false;
							}
							++i;
						}

						//if there a non consecutive negative sign after e
						if (subset.find('-', i + 2) != -1)
						{
							return false;
						}
					}
				}

				//if the negative or positive sign does not go before an e and is not the first element
				else if (subset[i] == '-' || subset[i] == '+')
				{
					//if a plus or minus symbol is not the first element it should precede an e
					if (i != 0 && subset[i-1] != 'e')
					{
						return false;
					}
					
					//if e goes after a + or - that is not allowed
					if (s[i + 1] == 'e')
					{
						return false;
					}
					//if there is not a number after a symbol then it is not a valid number
					if (!((subset[i+1] >= 48 && subset[i+1] <= 57) || subset[i+1] == 'e' || subset[i+1] == '.'))
					{
						return false;
					}

				}
				//if dot
				else if (subset[i] == '.')
				{
					//neither e, - not + is allowed after dot
					if (subset.find('e', i + 1) != -1)
					{
						//if there an e after the dot there should be a number after e
						if (i + 2 == subset.size())
						{
							return false;
						}
						//if dot is the first element 
						if (i == 0)
						{
							//there should be a number after dot
							if (!(subset[i + 1] >= 48 && subset[i + 1] <= 57))
							{
								return false;
							}
						}
					}
				}
			}
		}
		//anything else is not valid
		else
		{
			return false;
		}
	}
	//checking if there are any spaces in between numbers
	if (!(SpaceChecker(s)))
	{
		return false;
	}
	return true;
}