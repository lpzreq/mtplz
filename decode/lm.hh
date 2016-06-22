#pragma once

#include "decode/feature.hh"
#include "lm/model.hh"
#include "lm/state.hh"
#include "util/layout.hh"

namespace util { class MutableVocab; }

namespace decode {

class LM : public Feature {
  public:
    LM(const char *model, util::MutableVocab &vocab);

    void Init(FeatureInit &feature_init) override;

    static const StringPiece Name();

    void NewWord(StringPiece string_rep, VocabWord *word) const override {}

    void ScorePhrase(PhrasePair phrase_pair, ScoreCollector &collector) const override {}

    void ScoreHypothesisWithSourcePhrase(
        const Hypothesis &hypothesis, const SourcePhrase source_phrase, ScoreCollector &collector) const override {}

    void ScoreHypothesisWithPhrasePair(
        const Hypothesis &hypothesis, PhrasePair phrase_pair, ScoreCollector &collector) const override;

    void ScoreFinalHypothesis(
        const Hypothesis &hypothesis, ScoreCollector &collector) const override {}

    std::size_t DenseFeatureCount() const override;

    std::string FeatureDescription(std::size_t index) const override;

    const lm::ngram::Model &Model() const { return model_; }
  private:
    lm::WordIndex Convert(ID from) const;

    lm::ngram::Model model_;
    std::vector<lm::WordIndex> vocab_mapping_;
    const pt::Access *phrase_access_;
    util::PODField<lm::ngram::Right> lm_state_field_; // TODO why two state objects?
    util::PODField<lm::ngram::ChartState> chart_state_field_;
    util::MutableVocab &vocab_;
};

} // namespace decode