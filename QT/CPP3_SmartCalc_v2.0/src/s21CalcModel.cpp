#include "s21CalcModel.h"

namespace s21 {

CalcModel::CalcModel() {}

CalcModel::~CalcModel() { del(); }

CalcModel::CalcModel(const CalcModel &other) : CalcModel() { copy(other); }

CalcModel &CalcModel::operator=(const CalcModel &other) {
  del();
  copy(other);
  return *this;
}

void CalcModel::del() {
  for (auto it = data_.begin(); it != data_.end(); ++it) {
    delete *it;
  }
  data_.clear();
  polish_.clear();
}

void CalcModel::copy(const CalcModel &other) {
  for (auto it = other.data_.begin(); it != other.data_.end(); ++it) {
    I_Arithmetic *data;
    std::stringstream ss;
    ss << **it;
    switch ((*it)->get_type()) {
      case numbers:
        data = new Number((dynamic_cast<Number *>(*it))->get_number());
        break;
      case operations:
        data = new Operations(ss.str()[0]);
        break;
      case functions:
        data = new Functions(ss.str());
        break;
      case brackets:
        data = new Bracket(ss.str()[0]);
        break;
      case unknowns:
        data = new Unknown();
        break;
      case unary:
        data = new UnaryOperations(ss.str()[0]);
        break;
    }
    data_.push_back(data);
  }
}

void CalcModel::pushBackArithmetic(I_Arithmetic *data) {
  data_.push_back(data);
}

void CalcModel::editBackArithmetic(I_Arithmetic *data) {
  clearBackArithmetic();
  pushBackArithmetic(data);
}

void CalcModel::clearBackArithmetic() {
  if (!data_.empty()) {
    auto it = data_.rbegin();
    delete *it;
    data_.pop_back();
  }
}

void CalcModel::clear() {
  for (auto it = data_.begin(); it != data_.end(); ++it) {
    delete *it;
  }
  data_.clear();
  polish_.clear();
}

std::string CalcModel::toString() {
  std::stringstream ss;
  for (auto it = data_.begin(); it != data_.end(); ++it) {
    if (it != data_.begin()) ss << " ";
    ss << **it;
  }
  std::string result = ss.str();
  return result;
}

std::string CalcModel::toStringLast() {
  std::stringstream ss;
  ss << *(data_.back());
  return ss.str();
};

bool CalcModel::isNumber() {
  if (!data_.empty()) {
    if (data_.back()->get_type() == numbers) {
      return true;
    }
  }
  return false;
}

bool CalcModel::isUnary() {
  if (data_.empty()) return true;
  if (data_.back()->get_type() == brackets) {
    Bracket *p = dynamic_cast<Bracket *>(data_.back());
    if (p->get_bracket() == '(') {
      return true;
    }
  }
  return false;
}

bool CalcModel::getCheck() {
  if (data_.empty()) throw std::invalid_argument("empty");
  auto it = data_.begin();
  auto it_next = it;
  ++it_next;
  for (; it_next != data_.end(); ++it, ++it_next) {
    Arithmetic_type t1 = (*it)->get_type();
    Arithmetic_type t2 = (*it_next)->get_type();

    if (t1 == t2) {
      if (t1 == brackets) {
        Bracket *p1 = dynamic_cast<Bracket *>(*it);
        Bracket *p2 = dynamic_cast<Bracket *>(*it_next);
        if (p1->get_bracket() != p2->get_bracket()) {
          throw std::invalid_argument("invalid input empty ()");
        }
      } else {
        throw std::invalid_argument("invalid input");
      }
    }
    if (t1 == functions && t2 != brackets) {
      throw std::invalid_argument("after function mast be (");
    }
  }
  if ((*it)->get_type() == functions) {
    throw std::invalid_argument("after function mast be (");
  }
  return true;
}

void CalcModel::getPolish() {
  if (data_.empty()) throw std::invalid_argument("empty");
  polish_.clear();
  std::list<I_Arithmetic *> stack;
  for (auto it = data_.begin(); it != data_.end(); ++it) {
    Arithmetic_type type = (*it)->get_type();
    if (type == numbers || type == unknowns) {
      polish_.push_back(*it);
    } else if (type == brackets) {
      Bracket *p = dynamic_cast<Bracket *>(*it);
      if (p->get_bracket() == '(') {
        stack.push_front(*it);
      } else {
        while (!stack.empty() && stack.front()->get_type() != brackets) {
          polish_.push_back(stack.front());
          stack.pop_front();
        }
        if (!stack.empty()) {
          stack.pop_front();
        } else {
          throw std::invalid_argument("no (");
        }
      }
    } else if (type == operations || type == functions || type == unary) {
      while (!stack.empty() &&
             stack.front()->get_priority() >= (*it)->get_priority()) {
        polish_.push_back(stack.front());
        stack.pop_front();
      }
      stack.push_front(*it);
    }
  }
  while (!stack.empty() && stack.front()->get_type() != brackets) {
    polish_.push_back(stack.front());
    stack.pop_front();
  }
  if (!stack.empty()) {
    throw std::invalid_argument("no ( )");
  }
}

double CalcModel::getResult(double x) {
  if (polish_.empty()) {
    throw std::invalid_argument("invalid polish");
  }
  std::list<Number> stack;
  for (auto it = polish_.begin(); it != polish_.end(); ++it) {
    Arithmetic_type type = (*it)->get_type();
    if (type == numbers) {
      stack.push_front(*(dynamic_cast<Number *>(*it)));
    } else if (type == unknowns) {
      stack.push_front(Number(x));
    } else if (type == operations) {
      Operations *op = dynamic_cast<Operations *>(*it);
      if (stack.size() < 2) {
        throw std::invalid_argument("no number for operations");
      }
      Number a = stack.front();
      stack.pop_front();
      Number b = stack.front();
      stack.pop_front();
      stack.push_front(op->get_result(b, a));
    } else if (type == functions) {
      Functions *f = dynamic_cast<Functions *>(*it);
      if (stack.size() < 1) {
        throw std::invalid_argument("no number for functions");
      }
      Number a = stack.front();
      stack.pop_front();
      stack.push_front(f->get_result(a));
    } else if (type == unary) {
      if (stack.size() < 1) {
        throw std::invalid_argument("no number for UnaryOperations");
      }
      UnaryOperations *op = dynamic_cast<UnaryOperations *>(*it);
      Number a = stack.front();
      stack.pop_front();
      stack.push_front(op->get_result(a));
    } else {
      throw std::invalid_argument("unknown type");
    }
  }
  if (stack.size() == 1) {
    return stack.front().get_number();
  } else {
    throw std::invalid_argument("error! stack not null");
  }
}

// std::ostream &operator<<(std::ostream &out, const CalcModel &value) {
//   return value.printList(out);
// }

// std::ostream &CalcModel::printList(std::ostream &out) const {
//   out << "CalcModel(" << data_.size() << ")";
//   if (data_.size() > 0) out << ":" << std::endl;
//   for (auto it = data_.begin(); it != data_.end(); ++it) {
//     if (it != data_.begin()) out << " ";
//     out << **it;
//   }
//   return out;
// }

}  // namespace s21
