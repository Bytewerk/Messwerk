#ifndef ACTIVATEABLE_H
#define ACTIVATEABLE_H

class Activateable
{
  private:
    unsigned m_activeParts;

  public:
    static const unsigned PART_PAGE = (1 << 0);
    static const unsigned PART_COVER = (1 << 1);
    static const unsigned PART_LOGGING = (1 << 2);

    Activateable(void);

    virtual void activate(unsigned requestingPart);
    virtual void deactivate(unsigned requestingPart);

    virtual bool isActive(void);
    virtual bool isPartActive(unsigned part);
};

#endif // ACTIVATEABLE_H
