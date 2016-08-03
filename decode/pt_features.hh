#pragma once

#include "decode/feature.hh"

namespace decode {

class PhraseTableFeatures : public Feature {
  public:
    PhraseTableFeatures() : Feature("phrase_table") {}

    void Init(FeatureInit &feature_init) override {
      UTIL_THROW_IF(!feature_init.phrase_access.dense_features, util::Exception,
          "requested phrase table score but feature values are missing in phrase access");
      phrase_access_ = &feature_init.phrase_access;
      pt_row_field_ = feature_init.pt_row_field;
    }

    static const StringPiece Name();

    void NewWord(const StringPiece string_rep, VocabWord *word) const override {}

    void InitPassthroughPhrase(pt::Row *passthrough) const override {}

    void ScorePhrase(PhrasePair phrase_pair, ScoreCollector &collector) const override {
      std::size_t i = 0;
      for (float feature : phrase_access_->dense_features(pt_row_field_(phrase_pair.target_phrase))) {
        collector.AddDense(i++, feature);
      }
    }

    void ScoreHypothesisWithSourcePhrase(
        const Hypothesis &hypothesis, const SourcePhrase source_phrase, ScoreCollector &collector) const override {}

    void ScoreHypothesisWithPhrasePair(
        const Hypothesis &hypothesis, PhrasePair phrase_pair, ScoreCollector &collector) const override {}

    void ScoreFinalHypothesis(
        const Hypothesis &hypothesis, ScoreCollector &collector) const override {}

    std::size_t DenseFeatureCount() const override {
      return phrase_access_->dense_features.size();
    }

    std::string FeatureDescription(std::size_t index) const override {
      assert(index < DenseFeatureCount());
      return "dense phrase table feature " + std::to_string(index);
    }

  private:
    const pt::Access *phrase_access_;
    util::PODField<const pt::Row*> pt_row_field_;
};

} // namespace decode