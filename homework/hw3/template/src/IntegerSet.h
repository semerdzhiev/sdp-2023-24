#pragma once

#include <iostream>
#include <set>

class IntegerSet {
private:
  //TODO Add implementation details here

public:
  IntegerSet();
  IntegerSet(const IntegerSet&);
  IntegerSet& operator=(const IntegerSet&);
  ~IntegerSet();

public:
  // Връща броя на елементите в множеството
  size_t size() const;

  /// Проверява дали две множества се състоят от едни и същи елементи
  bool equals(const IntegerSet&) const;

  /// Проверява дали елемент се съдържа в множеството
  bool contains(int) const;

  /// Проверява дали текущия обект е подмножество на друг
  bool subsetOf(const IntegerSet&) const;

  /// Връща обединението на две множества
  IntegerSet getUnion(const IntegerSet&) const;

  /// Връща сечението на две множества
  IntegerSet getIntersection(const IntegerSet&) const;

  /// Десериализира съдържанието на едно множество.
  /// Новата информация напълно заменя старата.
  void deserialize(std::istream&);

  /// Сериализира съдържанието на едно множество
  void serialize(std::ostream&) const;
};

inline std::istream& operator>>(std::istream& in, IntegerSet& set)
{
  set.deserialize(in);
  return in;
}

inline std::ostream& operator<<(std::ostream& out, const IntegerSet& set)
{
  set.serialize(out);
  return out;
}
