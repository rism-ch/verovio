/////////////////////////////////////////////////////////////////////////////
// Name:        options.h
// Author:      Laurent Pugin
// Created:     2005
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_OPTIONS_H__
#define __VRV_OPTIONS_H__

#ifdef CUSTOM_VEROVIO_OPTIONS
#include "custom_options.h"
#else

#include <map>
#include <string>
#include <vector>

//----------------------------------------------------------------------------

#include "attalternates.h"
#include "atttypes.h"

//----------------------------------------------------------------------------

namespace vrv {
    
class OptionGrp;

//----------------------------------------------------------------------------
// Default scaling (%) and spacing (units) values
//----------------------------------------------------------------------------

#define DEFAULT_SCALE 100
#define MIN_SCALE 1
#define MAX_SCALE 1000

//----------------------------------------------------------------------------
// Options
//----------------------------------------------------------------------------

// the space between each lyric line in units
#define TEMP_LYRIC_LINE_SPACE 5.0

// the key signature spacing factor
#define TEMP_KEYSIG_STEP 1.3

// the maximum angle of a slur
#define TEMP_SLUR_MAX_SLOPE (45 * M_PI / 180)
#define TEMP_SLUR_CURVE_FACTOR 40 // a factor to allow more (0) or less (100) curved slurs
#define TEMP_SLUR_HEIGHT_FACTOR 8 // high value means flatter slurs
#define TEMP_SLUR_CONTROL_POINT_FACTOR 5 // higher value means more curved at the end

/* Options parameters for mensural notation */
// Ratios of mensural notehead, accidental, aug. dot size to CMN for the same staff size
#define TEMP_MNOTEHEAD_SIZE_FACTOR 1.0
#define TEMP_MACCID_SIZE_FACTOR 1.0
#define TEMP_MAUGDOT_SIZE_FACTOR 1.0
// Width of the minima diamond relative to its height
#define TEMP_MINIMA_WIDTH_FACTOR 1.0
// Size of mensuration sign circle relative to space between staff lines
#define MSIGN_CIRCLE_DIAM 1.7
// Vertical position of center of mensuration sign as distance below top of the staff
#define MSIGN_STAFFLINES_BELOW_TOP 2.0
// Size of dot inside mensuration signs relative to space between staff lines
#define MSIGN_DOT_DIAM 0.4
// Relative size of figures in proportions
#define PROPRT_SIZE_FACTOR 1.0
// Linewidth for staff lines in mensural notation, rel. to "normal" width of staff lines */
#define MENSURAL_LINEWIDTH_FACTOR 1.0

//----------------------------------------------------------------------------
// Option defines
//----------------------------------------------------------------------------

enum option_BREAKS
{
    BREAKS_none = 0,
    BREAKS_auto,
    BREAKS_encoded
};
    
enum option_MEASURENUMBER
{
    MEASURENUMBER_system = 0,
    MEASURENUMBER_interval
};
    
//----------------------------------------------------------------------------
// Option
//----------------------------------------------------------------------------
    
/**
 * This class is a base class of each styling parameter
 */
class Option {
public:
    // constructors and destructors
    Option() {}
    virtual ~Option() {}
    virtual void CopyTo(Option *option);
    
    void SetKey(std::string key) { m_key = key; }
    std::string GetKey() const { return m_key; }
    
    virtual bool SetValueBool(bool value);
    virtual bool SetValueDbl(double value);
    virtual bool SetValue(std::string value);
    
    void SetInfo(std::string title, std::string description);
    std::string GetTitle() const { return m_title; }
    std::string GetDescription() const { return m_description; }
    
public:
    /**
     * Static maps used my OptionIntMap objects. Set in OptIntMap::Init
     */
    static std::map<int, std::string> s_breaks;
    static std::map<int, std::string> s_measureNumber;
protected:
    std::string m_title;
    std::string m_description;
    
private:
    std::string m_key;
};

//----------------------------------------------------------------------------
// OptionBool
//----------------------------------------------------------------------------

/**
 * This class is for boolean styling params
 */
class OptionBool : public Option {
public:
    // constructors and destructors
    OptionBool() {}
    virtual ~OptionBool() {}
    virtual void CopyTo(Option *option);
    void Init(bool defaultValue);
    
    virtual bool SetValueBool(bool value);
    virtual bool SetValueDbl(double value);
    virtual bool SetValue(std::string value);
    
    bool GetValue() const { return m_value; }
    bool GetDefault() const { return m_defaultValue; }
    bool SetValue(bool value);
  
private:
    //
public:
    //
private:
    bool m_value;
    bool m_defaultValue;
};

//----------------------------------------------------------------------------
// OptionDbl
//----------------------------------------------------------------------------

/**
 * This class is for integer styling params
 */
class OptionDbl : public Option {
public:
    // constructors and destructors
    OptionDbl() {}
    virtual ~OptionDbl() {}
    virtual void CopyTo(Option *option);
    void Init(double defaultValue, double minValue, double maxValue);
    
    virtual bool SetValueDbl(double value);
    virtual bool SetValue(std::string value);
    
    double GetValue() const { return m_value; }
    double GetDefault() const { return m_defaultValue; }
    double GetMin() const { return m_minValue; }
    double GetMax() const { return m_maxValue; }
    bool SetValue(double value);

private:
    //
public:
    //
private:
    double m_value;
    double m_defaultValue;
    double m_minValue;
    double m_maxValue;
};
    
//----------------------------------------------------------------------------
// OptionInt
//----------------------------------------------------------------------------

/**
 * This class is for integer styling params
 */
class OptionInt : public Option {
public:
    // constructors and destructors
    OptionInt() {}
    virtual ~OptionInt() {}
    virtual void CopyTo(Option *option);
    void Init(int defaultValue, int minValue, int maxValue, bool definitionFactor = false);
    
    virtual bool SetValueDbl(double value);
    virtual bool SetValue(std::string value);
    
    int GetValue();
    int GetUnfactoredValue();
    int GetDefault() const { return m_defaultValue; }
    int GetMin() const { return m_minValue; }
    int GetMax() const { return m_maxValue; }
    bool SetValue(int value);

private:
    //
public:
    //
private:
    int m_value;
    int m_defaultValue;
    int m_minValue;
    int m_maxValue;
    bool m_definitionFactor;
};

//----------------------------------------------------------------------------
// OptionString
//----------------------------------------------------------------------------

/**
 * This class is for string styling params
 */
class OptionString : public Option {
public:
    // constructors and destructors
    OptionString() {}
    virtual ~OptionString() {}
    virtual void CopyTo(Option *option);
    void Init(std::string defaultValue);
    
    virtual bool SetValue(std::string value);
    
    std::string GetValue() const { return m_value; }
    std::string GetDefault() const { return m_defaultValue; }

private:
    //
public:
    //
private:
    std::string m_value;
    std::string m_defaultValue;
};
    
//----------------------------------------------------------------------------
// OptionArray
//----------------------------------------------------------------------------

/**
 * This class is for array (string) styling params
 */
class OptionArray : public Option {
public:
    // constructors and destructors
    OptionArray() {}
    virtual ~OptionArray() {}
    virtual void CopyTo(Option *option);
    void Init(OptionGrp *grp = NULL);
    
    virtual bool SetValue(std::string value);
    
    std::vector<std::string> GetValue() const { return m_values; }
    std::vector<std::string> GetDefault() const { return m_defaultValues; }
    bool SetValue(std::vector<std::string> const &values);

private:
    //
public:
    //
private:
    std::vector<std::string> m_values;
    std::vector<std::string> m_defaultValues;
};

//----------------------------------------------------------------------------
// OptionIntMap
//----------------------------------------------------------------------------

/**
 * This class is for map break options
 */
class OptionIntMap : public Option {
public:
    // constructors and destructors
    OptionIntMap();
    virtual ~OptionIntMap() {}
    virtual void CopyTo(Option *option);
    void Init(int defaultValue, std::map<int, std::string> *values);
    
    virtual bool SetValue(std::string value);
    
    int GetValue() const { return m_value; }
    int GetDefault() const { return m_defaultValue; }
    bool SetValue(int value);

    std::string GetStrValue() const;
    std::string GetDefaultStrValue() const;
    std::vector<std::string> GetStrValues(bool withoutDefault) const;
    std::string GetStrValuesAtStr(bool withoutDefault) const;
private:
    //
public:
    //
private:
    std::map<int, std::string> *m_values;
    int m_value;
    int m_defaultValue;
};
    
//----------------------------------------------------------------------------
// OptionStaffrel
//----------------------------------------------------------------------------

/**
 * This class is for map styling params
 */
class OptionStaffrel : public Option {
public:
    // constructors and destructors
    OptionStaffrel() {};
    virtual ~OptionStaffrel() {};
    virtual void CopyTo(Option *option);
    // Alternate type style cannot have a restricted list of possible values
    void Init(data_STAFFREL defaultValue);
    
    virtual bool SetValue(std::string value);
    
    // For altenate types return a reference to the value
    // Alternatively we can have a values vector for each sub-type
    const data_STAFFREL *GetValueAlternate() const { return &m_value; }
    const data_STAFFREL *GetDefaultAlernate() const { return &m_defaultValue; }
    
private:
    //
public:
    //
private:
    data_STAFFREL m_value;
    data_STAFFREL m_defaultValue;
};
    
//----------------------------------------------------------------------------
// OptionStaffrelBasic
//----------------------------------------------------------------------------

/**
 * This class is for map styling params
 */
class OptionStaffrelBasic : public Option {
public:
    // constructors and destructors
    OptionStaffrelBasic() {};
    virtual ~OptionStaffrelBasic() {};
    virtual void CopyTo(Option *option);
    void Init(data_STAFFREL_basic defaultValue, const std::vector<data_STAFFREL_basic> &values);

    virtual bool SetValue(std::string value);
    
    data_STAFFREL_basic GetValue() const { return m_value; }
    data_STAFFREL_basic GetDefault() const { return m_defaultValue; }

private:
    //
public:
    //
private:
    std::vector<data_STAFFREL_basic> m_values;
    data_STAFFREL_basic m_value;
    data_STAFFREL_basic m_defaultValue;
};
    
//----------------------------------------------------------------------------
// OptionGrp
//----------------------------------------------------------------------------
    
/**
 * This class is a base class of each styling parameter
 */
class OptionGrp {
public:
    // constructors and destructors
    OptionGrp() {}
    virtual ~OptionGrp() {}
    
    void SetLabel(const std::string &label) { m_label = label; }
    std::string GetLabel() const { return m_label; }
    
    void AddOption(Option *option) { m_options.push_back(option); }
    
    const std::vector<Option *> *GetOptions() const { return &m_options; }
public:
    //
protected:
    std::string m_label;
    std::vector<Option *> m_options;
};

    
//----------------------------------------------------------------------------
// Options
//----------------------------------------------------------------------------
    
/**
 * This class contains the document styling parameters.
 */
class Options {
public:
    // constructors and destructors
    Options();
    virtual ~Options();
    
    Options(const Options &options);
    Options &operator=(const Options &options);
    
    const MapOfStrOptions *GetItems() const { return &m_items; }
    
    std::vector<OptionGrp *> *GetGrps() { return &m_grps; }
    
private:
    void Register(Option *option, std::string key, OptionGrp *grp);

public:
    /**
     * Comments in implementation file options.cpp
     */

    /**
     * General layout - to be sorted
     */
    OptionGrp m_generalLayout;

    OptionBool m_adjustPageHeight;
    OptionDbl m_barLineWidth;
    OptionInt m_beamMaxSlope;
    OptionInt m_beamMinSlope;
    OptionIntMap m_breaks;
    OptionBool m_evenNoteSpacing;
    OptionString m_font;
    OptionDbl m_graceFactor;
    OptionDbl m_hairpinSize;
    OptionBool m_humType;
    OptionBool m_landscape;
    OptionDbl m_leftPosition;
    OptionDbl m_lyricSize;
    OptionInt m_measureMinWidth;
    OptionIntMap m_measureNumber;
    OptionBool m_mmOutput;
    OptionBool m_noFooter;
    OptionBool m_noHeader;
    OptionBool m_noJustification;
    OptionInt m_pageHeight;
    OptionInt m_pageLeftMar;
    OptionInt m_pageRightMar;
    OptionInt m_pageTopMar;
    OptionInt m_pageWidth;
    OptionDbl m_slurMaxHeight;
    OptionDbl m_slurMinHeight;
    OptionDbl m_slurThickness;
    OptionDbl m_spacingLinear;
    OptionDbl m_spacingNonLinear;
    OptionInt m_spacingStaff;
    OptionInt m_spacingSystem;
    OptionDbl m_staffLineWidth;
    OptionDbl m_stemWidth;
    OptionDbl m_tieThickness;
    OptionInt m_unit;
    
    /**
     * Selectors
     */
    OptionGrp m_selectors;
    
    OptionArray m_appXPathQuery;
    OptionArray m_choiceXPathQuery;
    OptionString m_mdivXPathQuery;

    /**
     * Element margins
     */
    OptionGrp m_elementMargins;
    
    OptionDbl m_defaultBottomMargin;
    OptionDbl m_defaultLeftMargin;
    OptionDbl m_defaultRightMargin;
    OptionDbl m_defaultTopMargin;
    OptionDbl m_leftMarginAccid;
    OptionDbl m_leftMarginBarLine;
    OptionDbl m_leftMarginBeatRpt;
    OptionDbl m_leftMarginChord;
    OptionDbl m_leftMarginClef;
    OptionDbl m_leftMarginKeySig;
    OptionDbl m_leftMarginLeftBarLine;
    OptionDbl m_leftMarginMensur;
    OptionDbl m_leftMarginMeterSig;
    OptionDbl m_leftMarginMRest;
    OptionDbl m_leftMarginMRpt2;
    OptionDbl m_leftMarginMultiRest;
    OptionDbl m_leftMarginMultiRpt;
    OptionDbl m_leftMarginNote;
    OptionDbl m_leftMarginRest;
    OptionDbl m_leftMarginRightBarLine;
    OptionDbl m_rightMarginAccid;
    OptionDbl m_rightMarginBarLine;
    OptionDbl m_rightMarginBeatRpt;
    OptionDbl m_rightMarginChord;
    OptionDbl m_rightMarginClef;
    OptionDbl m_rightMarginKeySig;
    OptionDbl m_rightMarginLeftBarLine;
    OptionDbl m_rightMarginMensur;
    OptionDbl m_rightMarginMeterSig;
    OptionDbl m_rightMarginMRest;
    OptionDbl m_rightMarginMRpt2;
    OptionDbl m_rightMarginMultiRest;
    OptionDbl m_rightMarginMultiRpt;
    OptionDbl m_rightMarginNote;
    OptionDbl m_rightMarginRest;
    OptionDbl m_rightMarginRightBarLine;
    
private:
    /** The array of style parameters */
    MapOfStrOptions m_items;
    
    std::vector<OptionGrp *> m_grps;
};

} // namespace vrv

#endif // CUSTOM_VEROVIO_OPTIONS

#endif // __VRV_DEF_H__
