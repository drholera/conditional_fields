<?php
/**
 * @file
 * Contains conditional field's lists.
 */

/**
 * Builds a list of supported states that may be applied to a dependent field.
 */
function field_states_ui_states() {
  $states = array(
    'field_state_enabled'  => t('Enabled'),
    'field_state_disabled'   => t('Disabled'),

    'field_state_required'   => t('Required'),
    'field_state_optional'  => t('Optional'),

    'field_state_visible' => t('Visible'),
    'field_state_invisible' => t('Invisible'),

    'field_state_checked'    => t('Checked'),
    'field_state_unchecked'   => t('Unchecked'),

    'field_state_expanded' => t('Expanded'),
    'field_state_collapsed'  => t('Collapsed'),

    // TODO: Add support to these states (plugins):
    /*
    'field_state_relevant'   => t('Relevant'),
    'field_state_irrelevant'  => t('Irrelevant'),
    'field_state_valid'      => t('Valid'),
    'field_state_invalid'     => t('Invalid'),
    'field_state_touched'    => t('Touched'),
    'field_state_untouched'   => t('Untouched'),
    'field_state_readwrite'  => t('Read/Write'),
    'field_state_readonly'   => t('Read Only'),
    */
  );

  // Allow other modules to modify the states.
  \Drupal::moduleHandler()->alter('conditional_fields_states', $states);

  return $states;
}

/**
 * Builds a list of supported effects.
 *
 * That may be applied to a dependent field
 * when it changes from visible to invisible and viceversa. The effects may
 * have options that will be passed as Javascript settings and used by
 * conditional_fields.js.
 *
 * @return array
 *   An associative array of effects. Each key is an unique name for the effect.
 *   The value is an associative array:
 *   - label: The human readable name of the effect.
 *   - states: The states that can be associated with this effect.
 *   - options: An associative array of effect options names, field types,
 *     descriptions and default values.
 */
function conditional_fields_effects() {
  $effects = array(
    'show' => array(
      'label' => t('Show/Hide'),
      'states' => array('visible', '!visible'),
    ),
    'fade' => array(
      'label' => t('Fade in/Fade out'),
      'states' => array('visible', '!visible'),
      'options' => array(
        'speed' => array(
          '#type' => 'textfield',
          '#description' => t('The speed at which the animation is performed, in milliseconds.'),
          '#default_value' => 400,
        ),
      ),
    ),
    'slide' => array(
      'label' => t('Slide down/Slide up'),
      'states' => array('visible', '!visible'),
      'options' => array(
        'speed' => array(
          '#type' => 'textfield',
          '#description' => t('The speed at which the animation is performed, in milliseconds.'),
          '#default_value' => 400,
        ),
      ),
    ),
    'fill' => array(
      'label' => t('Fill field with a value'),
      'states' => array('!empty'),
      'options' => array(
        'value' => array(
          '#type' => 'textfield',
          '#description' => t('The value that should be given to the field when automatically filled.'),
          '#default_value' => '',
        ),
        'reset' => array(
          '#type' => 'checkbox',
          '#title' => t('Restore previous value when untriggered'),
          '#default_value' => 1,
        ),
      ),
    ),
    'empty' => array(
      'label' => t('Empty field'),
      'states' => array('empty'),
      'options' => array(
        'value' => array(
          '#type' => 'hidden',
          '#description' => t('The value that should be given to the field when automatically emptied.'),
          '#value' => '',
          '#default_value' => '',
        ),
        'reset' => array(
          '#type' => 'checkbox',
          '#title' => t('Restore previous value when untriggered'),
          '#default_value' => 1,
        ),
      ),
    ),
  );

  // Allow other modules to modify the effects.
  \Drupal::moduleHandler()->alter('conditional_fields_effects', $effects);

  return $effects;
}

/**
 * List of states of a dependee field that may be used to evaluate a condition.
 */
function field_states_ui_conditions($checkboxes = TRUE) {
  // Supported by States API.
  $conditions = array(
    'filled' => t('Filled'),
    'empty' => t('Empty'),
    // TODO Provide support for these conditions.
    /*'expanded' => t('Expanded'),
    'collapsed' => t('Collapsed'),
    'relevant'   => t('Relevant'),
    'irrelevant'  => t('Irrelevant'),
    'valid'      => t('Valid'),
    'invalid'     => t('Invalid'),
    'touched' => t('Touched'),
    'untouched' => t('Untouched'),
    'readwrite'  => t('Read/Write'),
    'readonly'   => t('Read Only'),*/
  );

  if ($checkboxes) {
    // Relevant only if dependee is a list of checkboxes.
    $conditions['checked'] = t('Checked');
    $conditions['unchecked'] = t('Unchecked');
  }

  $conditions['value'] = t('Value');

  // Allow other modules to modify the conditions.
  \Drupal::moduleHandler()->alter('conditional_fields_conditions', $conditions);

  return $conditions;
}

/**
 * List of behaviors that can be applied when editing forms and viewing content
 * with dependencies.
 */
function conditional_fields_behaviors($op = NULL) {
  $behaviors = array(
    'edit' => array(
      CONDITIONAL_FIELDS_FIELD_EDIT_HIDE_ORPHAN => t('Hide the dependent if the dependee is not in the form'),
      CONDITIONAL_FIELDS_FIELD_EDIT_RESET_UNTRIGGERED => t('Reset the dependent to its default values when the form is submitted if the dependency is not triggered.') . '<br /><em>' . t('Note: This setting only applies if the condition is "Value", "Empty", or "Filled" and may not work with some field types. Also, ensure that the default values are valid, since they will not be validated.') . '</em>',
      // TODO: Implement. Settings are imported from D6 though, they just do nothing for now.
      /*
      CONDITIONAL_FIELDS_FIELD_EDIT_HIDE_UNTRIGGERED_ORPHAN => t('Hide the dependent if the dependee is not in the form and the dependency is not triggered.') . '<br /><em>' . t('Note: This setting is not currently not implemented and has no effect.') . '</em>',
      */
    ),
    'view' => array(
      CONDITIONAL_FIELDS_FIELD_VIEW_EVALUATE => t('Hide the dependent if the dependency is not triggered'),
      CONDITIONAL_FIELDS_FIELD_VIEW_HIDE_ORPHAN => t('Hide the dependent if the dependee is not viewable by the user'),
      CONDITIONAL_FIELDS_FIELD_VIEW_HIDE_UNTRIGGERED_ORPHAN => t('Hide the dependent if the dependee is not viewable by the user and the dependency is not triggered'),
      CONDITIONAL_FIELDS_FIELD_VIEW_HIGHLIGHT => t('Theme the dependent like an error message if the dependency is not triggered'),
      CONDITIONAL_FIELDS_FIELD_VIEW_DESCRIBE => t('Show a textual description of the dependency under the dependent'),
    ),
  );

  // Allow other modules to modify the options.
  \Drupal::moduleHandler()->alter('conditional_fields_behaviors', $behaviors);

  if (isset($behaviors[$op])) {
    return $behaviors[$op];
  }

  return $behaviors;
}
