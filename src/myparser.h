#include "../dmlc-core/src/data/csv_parser.h"

namespace dmlc {
namespace data {
        /*
struct MyParserParam :public MyParserParam {
    int label_column;
};

class MyParser : public MyParser {


};
*/

struct MyParserParam : public CSVParserParam {//Parameter<MyParserParam> {
  std::string format;
  int label_column;
  // declare parameters
//  DMLC_DECLARE_PARAMETER(MyParserParam) {
//    DMLC_DECLARE_FIELD(format).set_default("My")
//        .describe("File format.");
//    DMLC_DECLARE_FIELD(label_column).set_default(14)
//        .describe("Column index that will put into label.");
//  }
};


/*!
 * \brief MyParser, parses a dense My format.
 *  Currently is a dummy implementation, when label column is not specified.
 *  All columns are treated as real dense data.
 *  label will be assigned to 0.
 *
 *  This should be extended in future to accept arguments of column types.
 */
template <typename IndexType>
class MyParser : public TextParserBase<IndexType> {
 public:
  explicit MyParser(InputSplit *source,
                     const std::map<std::string, std::string>& args,
                     int nthread)
      : TextParserBase<IndexType>(source, nthread) {
    param_.Init(args);
    CHECK_EQ(param_.format, "My");
  }

 protected:
  virtual void ParseBlock(char *begin,
                          char *end,
                          RowBlockContainer<IndexType> *out);

 private:
  MyParserParam param_;
};

template <typename IndexType>
void MyParser<IndexType>::
ParseBlock(char *begin,
           char *end,
           RowBlockContainer<IndexType> *out) {
  out->Clear();
  std::cout << "hahain"<< std::endl;
  char * lbegin = begin;
  char * lend = lbegin;
  while (lbegin != end) {
    // get line end
    lend = lbegin + 1;
    while (lend != end && *lend != '\n' && *lend != '\r') ++lend;

    char* p = lbegin;
    int column_index = 0;
    IndexType idx = 0;
    float label = 0.0f;

    while (p != lend) {
      char *endptr;
      float v = strtof(p, &endptr);
      p = endptr;
      if (column_index == param_.label_column) {
        label = v;
      } else {
        out->value.push_back(v);
        out->index.push_back(idx++);
      }
      ++column_index;
      while (*p != ',' && p != lend) ++p;
      if (p != lend) ++p;
    }
    // skip empty line
    while ((*lend == '\n' || *lend == '\r') && lend != end) ++lend;
    lbegin = lend;
    out->label.push_back(label);
    out->offset.push_back(out->index.size());
  }
  CHECK(out->label.size() + 1 == out->offset.size());
}

template<typename IndexType>
Parser<IndexType> *
CreateMyParser(const std::string& path,
                const std::map<std::string, std::string>& args,
                unsigned part_index,
                unsigned num_parts) {
  InputSplit* source = InputSplit::Create(
      path.c_str(), part_index, num_parts, "text");
  return new MyParser<IndexType>(source, args, 2);
}
}
}
