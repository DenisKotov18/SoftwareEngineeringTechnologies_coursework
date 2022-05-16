#include "DataPart.h"

void assortmentManagment(User &user)
{
	Product* products = NULL;
	int products_count = 0; // Кол-во пользователей
	readDataFile(products, products_count);
	if (user.role == 0)
	{
		dataManipulation(products, products_count);
		return;
	}
	while (true)
	{
		switch (menu(MANAGEMENT_HEAD, MANAGEMENT_MENU))
		{
		case 0: dataRedact(products, products_count); break;
		case 1: dataManipulation(products, products_count); break;
		case 2:
		{
			if (products_count > 0)delete[]products;
			return;
		}
		}
	}
}

void dataRedact(Product*& products, int& products_count)
{
	while (true)
	{
		switch (menu(DATA_RED_HEAD, DATA_RED_MENU))
		{
		case 0: 
		{
			if (products_count > 0) showRedactData(products, products_count);
			else
			{
				system("cls");
				cout << DATA_EMPTY << endl;
				system("pause");
			}
			break;
		}
		case 1: newData(products, products_count); break;
		case 2: return;
		default:
			break;
		}
	}
}

void newData(Product*& products, int& products_count)
{
	Product new_product = { '\0', '\0', '\0', 0, 0 };
	
	system("cls");
	if ((inputArticle(new_product) == -1) ||
		(inputDataNames(new_product.name, INPUT_PRODUCT_NAME) == NULL) ||
		(inputDataNames(new_product.producer, INPUT_PRODUCER_NAME) == NULL) ||
		(inputPrice(new_product) == -1) ||
		(inputSize(new_product) == -1) ||
		(inputAmount(new_product) == -1)) return;
	if(menu((string)FINAL_PRODUCT + '\n'
		+ FINAL_NAME+ new_product.name + '\n'
		+ FINAL_ARTICLE + new_product.article + '\n'
		+ FINAL_PRODUCER + new_product.producer + '\n'
		+ FINAL_PRICE + to_string(new_product.price) + '\n'
		+ FINAL_SIZE + to_string(new_product.size) + '\n'
		+ FINAL_AMOUNT + to_string(new_product.amount) + '\n' + FINAL_CONFIRMATION,
		CONFIRM) == 0)
	{
		if (searchSimilarData(products, new_product, products_count) == false)
		{
			productMemoryReallocation(products, new_product, products_count);
			addDataToFile(new_product);
		}
		else
		{
			cout << endl << MATCH_FOUND << endl;
			writeToData(products, products_count);
		}
		doneFunc();
	}
	else canselFunc();
}

void dataManipulation(Product*& products, int& products_count)
{
	if (products_count < 1)
	{
		system("cls");
		cout << DATA_EMPTY << endl;
		system("pause");
		return;
	}
	while (true)
	{
		switch (menu(DATA_MANIPULATION_HEAD, DATA_MANIPULATION_MENU))
		{
		case 0: dataTable(products, products_count, "\0");
			break;
		case 1: individualTask(products, products_count);
			break;
		case 2: sortMenu(products, products_count);
			break;
		case 3:
			return;
		}
	}
}

bool searchSimilarData(Product*& products, Product& product, int& products_count)
{
	int possible_pos = 0;
	while (searchByProducer(products, product, possible_pos, products_count) == true)
	{
		if (compareByName(products[possible_pos], product) == true ||
			compareByArticle(products[possible_pos], product) == true ||
			compareBySize(products[possible_pos], product) == true)
			products[possible_pos].amount += product.amount;
			return true;
	}
	return false;
}

bool compareByName(Product& ex_product, Product& product)
{
	if (isSimilar(ex_product.name, product.name) == true)
		return true;
	return false;
}

bool compareByArticle(Product& ex_product, Product& product)
{
	if (ex_product.article == product.article)
		return true;
	return false;
}

bool compareBySize(Product& ex_product, Product& product)
{
	if (ex_product.size == product.size)
		return true;
	return false;
}

void individualTask(Product*& products, int& products_count)
{
	Product search_prototype;
	if (inputArticle(search_prototype) == -1) return;
	if (inputSize(search_prototype) == -1) return;

	Product* sorted_list = new Product;
	int sorted_count = 0;
	for (int i = 0; i < products_count; i++)
	{
		if (compareByArticle(products[i],search_prototype) == true)
			if (compareBySize(products[i], search_prototype) == true)
				productMemoryReallocation(sorted_list, products[i], sorted_count);
	}
	if (sorted_count != 0)dataTable(sorted_list, sorted_count, "\0");
	else
	{
		cout << SORT_DATA_NOT_FOUND;
		system("pause");
	}
	delete[]sorted_list;
}

void sortMenu(Product*& products, int& products_count)
{
	while (true)
	{
		switch (menu(SORT_MENU_HEAD, SORT_MENU_POINTS))
		{
		case 0: sortByAmount(products, products_count);
			break;
		case 1: sortBySize(products, products_count);
			break;
		case 2: sortByPrice(products, products_count);
			break;
		case 3:
			return;
		}
		dataSync(products, products_count);
	}
}

bool searchByProducer(Product*& products, Product& product, int& last, int& products_count)
{
	for (int i = last + 1; i < products_count; i++)
	{
		if (isSimilar(products[i].producer, product.producer) == true)
		{
			last = i;
			return true;
		}
	}
	return false;
}

void sortBySize(Product*& products, int& products_count)
{
	int counter = 0;
	while (counter != products_count - 1)
	{
		if (products[counter].size > products[counter + 1].size)
		{
			swap(products[counter], products[counter + 1]);
			if (counter > 0) counter -= 2;
		}
		counter++;
	}
	sortByOrder(products, products_count);
}

void sortByPrice(Product*& products, int& products_count)
{
	int counter = 0;
	while (counter != products_count - 1)
	{
		if (products[counter].price > products[counter + 1].price)
		{
			swap(products[counter], products[counter + 1]);
			if (counter > 0) counter -= 2;
		}
		counter++;
	}
	sortByOrder(products, products_count);
}

void sortByAmount(Product*& products, int& products_count)
{
	int counter = 0;
	while (counter != products_count - 1)
	{
		if (products[counter].amount > products[counter + 1].amount)
		{
			swap(products[counter], products[counter + 1]);
			if (counter > 0) counter -= 2;
		}
		counter++;
	}
	sortByOrder(products, products_count);
}

void sortByOrder(Product*& products, int& products_count)
{
	if (menu(SORT_QUESTION, SORT_POINTS) == 1)
	{
		int i = 0,
			j = products_count-1;
		while (i < j)
		{
			swap(products[i], products[j]);
			i++;
			j--;
		}
	}
	dataTable(products, products_count, "\0");
}

int inputArticle(Product& product)
{
	switch (menu(INPUT_ARTICLE, ARTICLE_POINTS))
	{
	case 0: product.article = 'М'; break;
	case 1: product.article = 'Ж'; break;
	case 2: product.article = 'Д'; break;
	case 3: canselFunc(); return -1;
	}
	return 0;
}

char* inputDataNames(char* const& product_data, const char message[])
{
	cout << endl << message;
	char* name = inputWord(product_data, NAME_LENGTH, false);
	if (name == NULL) canselFunc();
	return name;
}

int inputPrice(Product& product)
{
	cout << endl << INPUT_PRICE;
	product.price = getDouble(INPUT_PRICE);
	while (product.price < 0)
	{
		if (product.price == 0)
		{
			canselFunc();
			return -1;
		}
		cout << '	' << PRICE_ERROR << endl;
		cout << endl << INPUT_PRICE;
		product.price = getInt(INPUT_PRICE);
	}
	return 0;
}

int inputSize(Product &product)
{
	int size = 0;
	switch (product.article)
	{
	case 'Д':
	{
		size = checkRange(CHILD_MIN_SIZE, CHILD_MAX_SIZE, 0, INPUT_CHILD_SIZE);
		if (size != 0)
		{
			product.size = size;
			return 0;
		}
		break;
	}
	case 'М':case 'Ж':
	{
		size = checkRange(CHILD_MAX_SIZE, ADULT_SIZE, 0, INPUT_ADULT_SIZE);
		if (size != 0)
		{
			product.size = size;
			return 0;
		}
		break;
	}
	}
	canselFunc();
	return -1;
}

int inputAmount(Product& product)
{
	cout << endl << INPUT_AMOUNT;
	product.amount = getInt(INPUT_AMOUNT);
	
	while (product.amount < 1)
	{
		if (product.amount == 0)
		{
			canselFunc();
			return -1;
		}
		cout << '	' << AMOUNT_ERROR << endl;
		cout << endl << INPUT_AMOUNT;
		product.amount = getInt(INPUT_AMOUNT);
	}
	return 0;
}

void productMemoryReallocation(Product*& products, Product& new_product, int& products_count)
{
	Product* re_products = new Product[products_count + 1];

	for (int i = 0; i < products_count; i++) re_products[i] = products[i];
	re_products[products_count] = new_product;
	products_count++;
	delete[]products;
	products = re_products;
}

void showRedactData(Product*& products, int& products_count)
{
	while(true)
	{
		if (products_count > 0 && dataTable(products, products_count, ENTER_DATA) == 0)
		{
			int choise = checkRange(0, products_count, 0, DATA_CHOOSE);
			if (choise != 0) 
			{
				switch (productRedact(products[choise - 1]))
				{
				case -1: delData(products, products_count, choise - 1); break;
				case 0: writeToData(products, products_count); break;
				case 1:
				{
					dataSync(products, products_count);
					break;
				}
				}
			}
		}
		else return;
	}
}

int dataTable(Product*& products, int& products_count, const char message[])
{
	int	trash = 0,
		page = 0,
		first_visible = 0,
		last_visible = 0;
	bool uncorrect_flag = false;

	while (true)
	{
		system("cls");
		first_visible = NUMBER_OF_VISIBLE * page;
		last_visible = (first_visible + NUMBER_OF_VISIBLE < products_count) ? first_visible + NUMBER_OF_VISIBLE : products_count;

		cout << ' ' << setfill('_') << setw(35) << '_' << '|' << TABLE_ASSORTMENT << '|' << setw(35) << '_' << setfill(' ') << endl;
		for (int i = first_visible; i < last_visible; i++)
		{
			cout << ' ' << i + 1 << ". " << FINAL_NAME << "\033[35m" << setw(30)  << left << products[i].name << "\033[0m "
				<< FINAL_PRODUCER  << "\033[36m" << setw(30) << left << products[i].producer << endl << "\033[0m	"
				<< FINAL_PRICE << "\033[32m" << products[i].price << "\033[0m, " << FINAL_ARTICLE << "\033[32m" << products[i].article << "\033[0m, "
				<< FINAL_SIZE << "\033[32m" << products[i].size << "\033[0m, " << FINAL_AMOUNT << "\033[32m" << products[i].amount << "\033[0m" << endl << endl;
		}
		cout << ' ' << setfill('_') << setw(35) << '_' << '|' << TABLE_ASSORTMENT << '|' << setw(35) << '_' << setfill(' ') << endl
			<< '<' << setw(42) << right << page + 1 << '/' << setw(38) << left << ((products_count - 1) / NUMBER_OF_VISIBLE + 1) << '>' << endl
			<< endl << message << endl << ESC;
		do
		{
			uncorrect_flag = false;
			switch (_getch())
			{
			case '\r': return 0;
			case 27: return 1;
			case 224:
			{
				int intermediate = pointerCatcher(trash, first_visible, last_visible, page, ((products_count - 1) / NUMBER_OF_VISIBLE + 1));
				if (page == intermediate)
					uncorrect_flag = true;
				else page = intermediate;
				break;
			}
			default: uncorrect_flag = true;
			}
		} while (uncorrect_flag == true);
	}
}

int productRedact(Product& product)
{
	bool redact_flag = false;

	while (true)
	{
		system("cls");
		switch (menu((string)PRODUCT_REDACT_HEAD + '\n'
			+ FINAL_NAME + product.name + '\n'
			+ FINAL_PRICE + to_string(product.price) + '\n'
			+ FINAL_ARTICLE + product.article + '\n'
			+ FINAL_PRODUCER + product.producer + '\n'
			+ FINAL_SIZE + to_string(product.size) + '\n'
			+ FINAL_AMOUNT + to_string(product.amount) + '\n', PRODUCT_REDACT_MENU))
		{
		case 0:
		{
			if (inputDataNames(product.name, INPUT_PRODUCT_NAME) != NULL)
			{
				redact_flag = true;
				doneFunc();
			}
			break;
		}
		case 1: 
		{
			if(inputDataNames(product.producer, INPUT_PRODUCER_NAME) != NULL) 
			{
				redact_flag = true;
				doneFunc();
			}
			break;
		}
		case 2:
		{
			if (inputPrice(product) == 0)
			{
				redact_flag = true;
				doneFunc();
			}
			break;
		}
		case 3:
		{
			char backup_article = product.article;
			if (inputArticle(product) == 0)
			{
				if ((product.article == 'Д' && product.size > CHILD_MAX_SIZE) ||
					((product.article == 'М' || product.article == 'Ж') && product.size < CHILD_MAX_SIZE))
				{
					cout << endl << ERROR_ARTICLE_SIZE << endl;
					if (inputSize(product) == -1)
					{
						product.article = backup_article;
						break;
					}
				}
				redact_flag = true;
				doneFunc();
			}
			break;
		}
		case 4:
		{
			if (inputSize(product) == 0)
			{
				redact_flag = true;
				doneFunc();
			}
			break;
		}
		case 5:
		{
			if (inputAmount(product) == 0)
			{
				redact_flag = true;
				doneFunc();
			}
			break;
		}
		case 6: 
		{
			if (menu(DATA_DELETE, INTENTIONAL_CONFIRM) == 1) return -1;
			canselFunc();
			break;
		}
		case 7:
		{
			if (redact_flag == true && menu(SAVE_CONFIRM, CONFIRM) == 0)
			{
				doneFunc();
				return 0;
			}
			else return 1;
		}
		}
	}
}

void delData(Product*& products, int& products_count, const int del_pos)
{
	for (int i = del_pos; i < products_count - 1; i++)
		products[i] = products[i + 1];
	products_count--;
	writeToData(products, products_count);
	doneFunc();
}

void dataSync(Product*& products, int& products_count)
{
	delete[]products;
	readDataFile(products, products_count);
}