#include "ClassBook.h"

BookInfo::BookInfo(const std::string& bookName, const std::string& authorName, const int quantity)
	: bookName(bookName),
	authorName(authorName),
	copiesQuantity(quantity)
{
}

//functions "to_json" and "from_json" to work with Object "BookInfo"
void to_json(json& BookStorage, const BookInfo& p) {
	BookStorage = json{ {BookName, p.bookName}, {AuthorName, p.authorName}, {BookQuantity, p.copiesQuantity} };
}

void from_json(const json& BookStorage, BookInfo& p) {
	BookStorage.at(BookName).get_to(p.bookName);
	BookStorage.at(AuthorName).get_to(p.authorName);
	BookStorage.at(BookQuantity).get_to(p.copiesQuantity);
}