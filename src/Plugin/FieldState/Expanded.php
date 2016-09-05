<?php

namespace Drupal\field_states_ui\Plugin\FieldState;

use Drupal\Core\Form\FormStateInterface;
use Drupal\field_states_ui\FieldStateBase;

/**
 * Control details field widget check state in relation to other fields dynamically.
 *
 * @FieldState(
 *   id = "field_state_expanded",
 *   label = @Translation("Expanded"),
 *   description = @Translation("Dynamically collapse details field elements dependent on other field states/values.")
 * )
 */
class Collapsed extends FieldStateBase {

  /**
   * {@inheritdoc}
   */
  public function applyState(array &$states, FormStateInterface $form_state, array $context) {
    $states['expanded'] = [
      ':input[name="' . $this->configuration['dependee'] . '"]' => [
        $this->configuration['settings']['condition'] => $this->configuration['settings']['value'],
      ],
    ];
    return TRUE;
  }

}
