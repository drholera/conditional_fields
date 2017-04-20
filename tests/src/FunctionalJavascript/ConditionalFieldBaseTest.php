<?php

namespace Drupal\Tests\conditional_fields\FunctionalJavascript;

use Drupal\FunctionalJavascriptTests\JavascriptTestBase;

/**
 * Base setup for ConditionalField tests.
 */
abstract class ConditionalFieldBaseTest extends JavascriptTestBase {

  /**
   * The entity manager service.
   *
   * @var \Drupal\Core\Entity\EntityManagerInterface
   */
  protected $entityManager;

  /**
   * Access controller.
   *
   * @var \Drupal\Core\Entity\EntityAccessControlHandlerInterface
   */
  protected $accessControlHandler;

  /**
   * {@inheritdoc}
   */
  public static $modules = [
    'conditional_fields',
    'node',
    'datetime',
    'field_ui',
    'taxonomy',
  ];

  /**
   * {@inheritdoc}
   */
  public function __construct($name, array $data, $dataName) {
    $this->entityManager = \Drupal::service('entity.manager');
    $this->accessControlHandler = $this->entityManager->getAccessControlHandler('node');
    parent::__construct($name, $data, $dataName);
  }

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();

    // Create Basic page and Article node types.
    if ($this->profile != 'standard') {
      $this->drupalCreateContentType([
        'type' => 'page',
        'name' => 'Basic page',
        'display_submitted' => FALSE,
      ]);
      $this->drupalCreateContentType([
        'type' => 'article',
        'name' => 'Article',
      ]);
    }
  }

  /**
   * Waits and asserts that a given element is visible.
   *
   * @param string $selector
   *   The CSS selector.
   * @param int $timeout
   *   (Optional) Timeout in milliseconds, defaults to 1000.
   * @param string $message
   *   (Optional) Message to pass to assertJsCondition().
   */
  protected function waitUntilVisible($selector, $timeout = 1000, $message = '') {
    $condition = "jQuery('{$selector}').is(':visible');";
    $this->assertJsCondition($condition, $timeout, $message);
  }

  /**
   * Waits and asserts that a given element is hidden (invisible).
   *
   * @param string $selector
   *   The CSS selector.
   * @param int $timeout
   *   (Optional) Timeout in milliseconds, defaults to 1000.
   * @param string $message
   *   (Optional) Message to pass to assertJsCondition().
   */
  protected function waitUntilHidden($selector, $timeout = 1000, $message = '') {
    $condition = "jQuery('{$selector}').is(':hidden');";
    $this->assertJsCondition($condition, $timeout, $message);
  }

  /**
   * Helper to change Field value with Javascript.
   */
  protected function changeField($selector, $value = '') {
    $this->getSession()->executeScript("jQuery('" . $selector . "').val('" . $value . "').trigger('keyup').trigger('change');");
  }

  /**
   * Helper to change selection with Javascript.
   */
  protected function changeSelect($selector, $value = '') {
    $this->getSession()->executeScript("jQuery('" . $selector . "').val('" . $value . "').trigger('click').trigger('change');");
  }

  /**
   * Create basic fields' dependency.
   *
   * @param string $path
   *   The path to Conditional Field Form.
   * @param string $dependent
   *   Machine name of dependent field.
   * @param string $dependee
   *   Machine name of dependee field.
   * @param string $state
   *   Dependent field state.
   * @param string $condition
   *   Condition value.
   */
  protected function createCondition($path, $dependent, $dependee, $state, $condition) {
    $this->drupalGet($path);
    $this->assertSession()->statusCodeEquals(200);
    $edit = [
      'table[add_new_dependency][dependent][]' => $dependent,
      'table[add_new_dependency][dependee]' => $dependee,
      'table[add_new_dependency][state]' => $state,
      'table[add_new_dependency][condition]' => $condition,
    ];
    $this->submitForm($edit, 'Add dependency');
    $this->assertSession()->statusCodeEquals(200);
  }

}
