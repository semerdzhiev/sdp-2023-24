# Домашно 4: Поправителна сесия

## Описание

Фокусът на това домашно е върху реализацията на [префиксно дърво](https://en.wikipedia.org/wiki/Trie) и някои от основните операции с него.

Напишете програма, която получава като аргументи от командния ред пътищата на три текстови файла:

* един съдържащ думи, които са част от речник;
* втори, съдържащ думи, които трябва да се премахнат от речника (т.нар. "филтър");
* трети, който съдържа текст, който трябва да се провери спрямо получения речник;

При работата си програмата не трябва да прави разлика между големи и малки букви. Например между думите "ABC" и "abc" не трябва да се прави разлика.

Програмата трябва:

* Да зареди думите от речника и да ги съхрани в префиксно дърво.
* Да премахне от префиксното дърво всички думи съдържащи се във втория файл (филтъра).
* Да провери всички думи в текста спрямо получения речник и да изведе на екрана онези, които НЕ СЕ съдържат в речника.
* Да изведе на екрана кратка статистика:
  * брой коректни и брой некоректни записи в прочетения речник (броят се всички отделни записи; например, ако във файла има два записа "abc" и "ABC", те се броят като два отделни записа, въпреки че в работата си програмата няма да прави разлика между тях);
  * същата статистика да се изведе и за файла с думи за премахване;
  * брой думи, които реално са премахнати от речника;
  * брой на думите в получения след премахването речник;
  * брой на коректните и брой на сгрешените думи в текста (коректни са тези думи, които се срещат в получения речник).

За улеснение считаме, че думите в речника се състоят само от латинските букви (от `a` до `z`).

Ако в речника бъде открита некоректна дума (например съдържаща интервал, цифра и т.н.), трябва да се изведе съобщение за грешка, като се посочи на кой ред се намира некоректната дума. Работата на програмата трябва да продължи след това, като некоректната дума се игнорира.

Всяка дума в речника се изписва на отделен ред. Редовете започващи със символа `#` са коментари. Те трябва да се прескочат при обработката на тези файлове. Възможно е да има и празни редове или редове състоящи се само от празни (whitespace) символи, които трябва да се игнорират.

Редът, в който са подредени думите в речника не е определен. Може да е лексикографски, но може и да са в разбъркан ред. Възможно е да има и дублиращи се думи.

Всички правила за речника описани по-горе важат и за файла с думи, които да се премахнат от речника.

Текстът се състои от един или повече редове. Няма ограничение върху дължината на един ред или обема на целия текст. Думите в него се разделят помежду си с празни (whitespace) символи.

Върху броя на думите в речника и в текста не се поставя ограничение. Няма ограничение и върху максималната дължина на дума.

За улеснение ще считаме, че думите не са толкова дълги, че да не могат да се съберат в паметта. Също така, при прочитането на файловете и обработката на редовете можете да използвате `std::string`, `std::getline`, `std::istringstream` и `std::isalpha`.

Помислете за всички частни случаи, като например подаване на празен файл с текст или празен речник и реализирайте подходящо поведение на програмата.

## Примерно изпълнение

Съдържание на речника (`dictionary.txt`):

```text
# This is a comment. Its contents must be skipped.
XYZ
ab
ba

# The next four lines define the same word
aBcD
abcd
ABCD
abcd

# The following entries are incorrect
This is an incorrect entry, it has spaces.
 spaceOnTheLeft
spaceOnTheRight 
an0ther1ncorrectW0rd
```

Файл с думи, които да се премахнат от речника (`filter.txt`):

```text
# This line is a comment and must be ignored
xyz
abcabc

1234567890
```

Съдържание на текста (`text.txt`):

```text
abc ab abbcd abcd xyz
an0ther1ncorrectW0rd
```

Изпълнението може да изглежда например така:

```text
Loading dictionary from .\input\dictionary.txt...
ERROR: incorrect entry "This is an incorrect entry, it has spaces." on line 8
ERROR: incorrect entry " spaceOnTheLeft" on line 9
ERROR: incorrect entry "spaceOnTheRight " on line 10
ERROR: incorrect entry "an0ther1ncorrectW0rd" on line 11

Removing the words listed at .\input\filter.txt...
ERROR: incorrect entry "1234567890" on line 3

Verifying the contents of .\input\text.txt...
SPELLING ERROR: "abc" on line 1
SPELLING ERROR: "abbcd" on line 1
SPELLING ERROR: "xyz" on line 1
SPELLING ERROR: "an0ther1ncorrectW0rd" on line 2

Statistics:
    Dictionary entries: 7 correct, 4 incorrect
        Filter entries: 2 correct, 1 incorrect
  Resultant dictionary: 6
         Words in text: 2 correct, 4 incorrect
```

## Изисквания за реализацията

Решението ви трябва да включва описаните по-долу елементи. За всеки от тях в шаблона за домашното са включени съответните дефиниции.

### Библиотека `dictionarylib`

Изгражда се от файловете `Dictionary.h` и `Dictionary.cpp`.

Съдържа клас `Dictionary`, който представя речник и има като минимум следния интерфейс:

```cpp
class Dictionary {
public:
  void insert(const char* word);
  void erase(const char* word) noexcept;
  bool contains(const char* word) const noexcept;
  size_t size() const noexcept;
  static bool isCorrectWord(const char* word) noexcept;
};
```

В решението си не можете да променяте интерфейса на класа. Можете да добавите към него каквито прецените `private` членове, а също и допълнителни функции и/или класове.

Ако `insert` не може да добави думата по някаква причина, да се хвърли подходящо изключение. В частност, ако думата не е коректна, да се хвърли обект от следния клас:

```cpp
class incorrect_word_exception : public std::runtime_error {
public:
  incorrect_word_exception()
    : runtime_error("incorrect word")
  {
    // Nothing to do here
  }
};
```

Ако на `erase` бъде подадена дума, която не се съдържа в речника, тя не трябва да прави никакви промени в него. В частност, ако бъде подаден `nullptr`, да не се прави нищо (последното важи и за `contains`).

Вътрешно `Dictionary` трябва да реализира префиксно дърво (trie). Всеки елемент в него може да има най-много 26 наследника (колкото е броят на буквите в азбуката). Използвайте този факт, за да реализирате проста схема, чрез която бързо да можете да проверите дали след като стигнете до даден елемент и прочетете нов символ, съществува подходящ наследник към който да продължите или не.

За целите на задачата считаме, че възлите може да се представят по начин подобен на следния:

```cpp
class Node {
  Node* successors['Z'-'A'];
  // ...more implementation details follow...
}
```

Съответно, всяка позиция в масива съответства на преход със съответната буква.

Тази библиотека е покрита с тестове във файла `test-Dictionary.cpp`. Този файл не бива да се променя. Ако искате да добавите още тестове, създайте един или повече отделни файлове или използвайте подготвения за целта файл `test-Additional.cpp`.

### Приложение `application`

Изгражда се от `main.cpp`. В шаблона този файл е оставен празен. Сами преценете как да организирате кода в него. В частност, ако искате можете да добавите и други файлове с изходен код, да напишете подходящи unit test-ове и т.н.

Решението ви трябва да използва горе-описания клас `Dictionary`, за да реализира функционалността на програмата.

## Шаблон

Както и за предишните домашни, за това също е предоставен шаблон, в който да работите върху задачата. Той се намира в директорията `template/`.

Шаблонът съдържа unit test-ове, които проверяват само част от решението за коректност. Препоръчваме да ги допълните с подходящи проверки за останалата част от функционалността.

**ВАЖНО:** НЕ променяйте предоставения файл с unit test-ове, нито основния `CMakeLists.txt` файл. Вместо това, добавете един или повече нови файлове в папката `test/` и напишете в тях своите тестове. Можете да използвате и предварително подготвения за целта файл `test-Additional.cpp`.

Когато решавате домашното НЕ може да променяте следните:

* Помощните функции (ако такива са били предоставени в шаблона).
* Прототипите на функциите, които трябва да се реализират. Например, не може да променяте имената им, типовете на параметрите на функциите, типовете на връщаните стойности и т.н.
* Предоставените unit test-ове.
* `CMakeLists.txt` файла в основната директория на проекта.

В директорията `sample-inputs/` са предоставени няколко входни файла, с които можете да тествате приложението. Както и unit test-овете, те далеч не покриват всички възможни частни случаи. Допълнете ги по подходящ начин или създайте нови файлове, с които да проверите работата на програмата.

## Предаване на решението

Предайте решението си като един `.zip` архив. Включете в него само това, което е нужно, за да се изгради и тества решението.

**ВАЖНО:** Напомняме, че част от файловете в шаблона не бива да се променят. Уверете се, че предавате оригиналните версии заедно с работата си.

Освен ако НЕ СТЕ добавяли допълнителни директории, архивирайте и предайте само следните файлове/директории:

* `src/`
* `test/`
* `CMakeLists.txt`

Запазете структурата на шаблона. НЕ размествайте файловете, НЕ променяйте техните имена и т.н.

НЕ СЛАГАЙТЕ в архива временните файлове и директории генерирани от IDE-то, компилатора и т.н. (например `.vscode/`, `build/`, `out/` и т.н.).

**СЪВЕТ:** Би трябвало архивът да е с размер по-малък от 1MB, даже много по-малко (за тази задача вероятно ще е от порядъка на килобайти). Ако предавате архив с голям обем (например 30MB), със сигурност в него сте включили излишни неща.

След като предадете решението, за да се уверите, че всичко е оформено коректно, свалете архива от Moodle и проверете дали изграждането и тестовете преминават без грешки. За целта:

1. Свалете архива от Moodle.
1. Разархивирайте го в отделна, нова директория, например `C:\Temp\sdp-homework`.
1. Изградете решението си и пуснете тестовете. Всички стъпки трябва да преминават без грешки. Например, за директорията по-горе стъпките биха изглеждали така:

```bash
cd "C:\Temp\sdp-homework"
cmake -S . -B ./build
cmake --build ./build
ctest --test-dir ./build
```