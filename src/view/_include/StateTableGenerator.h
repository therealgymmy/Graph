// Copyright (C) 2012 Jimmy Lu //

// Compile time state table generator
// Refer to doc for more details

#ifndef STATE_TABLE_GENERATOR_H
#define STATE_TABLE_GENERATOR_H

namespace StateTableGenerator {

//---------------------------Public Api-----------------------------//

template <unsigned InputSize, unsigned StateSize, typename S> struct Table;

template <unsigned InputSize, unsigned StateSize, typename S, typename F>
constexpr Table<InputSize, StateSize, S> create (F next);



//-------------------------Implementation---------------------------//



//  <-- Number Sequence Generator Module --> //

template <unsigned... Is>
struct BaseSequence {};

template <unsigned N, unsigned... Is>
struct GenerateSequence : GenerateSequence <N - 1, N - 1, Is...> {};

template <unsigned... Is>
struct GenerateSequence <0, Is...> : BaseSequence <Is...> {};

template <unsigned N>
constexpr
GenerateSequence<N> seq () { return GenerateSequence<N>{}; }



//  <-- Table Module --> //

template <unsigned InputSize, unsigned StateSize, typename S>
struct Table {
    struct Row {
        S states_[InputSize];
        const S& operator[] (unsigned i) const { return states_[i]; }
        S&       operator[] (unsigned i)       { return states_[i]; }
    };

    const Row& operator[] (unsigned i) const { return rows_[i]; }
    Row&       operator[] (unsigned i)       { return rows_[i]; }

    Row rows_[StateSize];

    typedef S StateType;
};

template <unsigned InputSize, unsigned StateSize, typename S>
using TableRow = typename Table<InputSize, StateSize, S>::Row;



// <-- Table Generation Module -->

template <unsigned InputSize, unsigned StateSize,
          typename S, typename F,
          unsigned... IN>
constexpr
TableRow<InputSize, StateSize, S>
initExpand (F next, S state, BaseSequence<IN...>)
{
    return TableRow<InputSize, StateSize, S>{{ next(state, IN)... }};
}

template <unsigned InputSize, unsigned StateSize,
          typename S, typename F,
          unsigned... TS, unsigned... IN>
constexpr
Table<InputSize, StateSize, S>
initialize (F next,
            BaseSequence<TS...>,
            BaseSequence<IN...> inputs)
{
    return Table<InputSize, StateSize, S>{{
        initExpand<InputSize, StateSize>(next, S(TS), inputs)...
    }};
}

template <unsigned InputSize, unsigned StateSize,
          typename S, typename F>
constexpr
Table<InputSize, StateSize, S>
create (F next)
{
    return initialize<InputSize, StateSize, S>(next, seq<StateSize>(), seq<InputSize>());
}



}

namespace stg = StateTableGenerator;

#endif//STATE_TABLE_GENERATOR_H
