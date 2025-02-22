#ifndef MODEL_HPP
#define MODEL_HPP

class Model {
  public:
    int id;
    virtual ~Model() = default;

    Model() {}

    Model(int id) : id(id) {}
};

#endif // MODEL_HPP
