#ifndef COMPONENTMANAGERTEST_H
#define COMPONENTMANAGERTEST_H

#include <QtCore/QObject>

class ComponentManagerTest : public QObject
{
    Q_OBJECT
public:
    ComponentManagerTest();

private slots:
    void addComponent_shouldAddComponentToTheStoppedComponents();
    void addComponent_shouldSetCheckedFlagToFalse();

    void check_shouldCallResolving();
    void check_shouldSetCheckedFlag();
    void check_shouldNotResolveComponentsAgainIfCheckedFlagIsTrue();

    // orphan, missing components during startup
    void check_shouldFillMissingComponents();
    void check_shouldFillOrphanComponents();

    // startup activities
    void startupAllComponents_shouldCallCheck(); // which calls resolving
    void startupAllComponents_shouldRemoveThemFromStoppedList();
    void startupAllComponents_shouldAddThemToTheStartedList();
    void startupAllComponents_shouldEmit();
    void startupAllComponents_shouldStartComponents();
    void startupAllComponents_shouldPassInitDataToComponent();
    void startupAllComponents_shouldNotStartUnexistingComponent();
    void startupAllComponents_shouldNotStartDisabledComponent();
    void startupAllComponents_shouldHandleNullComponent();
    void startupAllComponents_shouldNotStartChildComponentsIfParentCouldNotStart();
    void startupAllComponents_shouldStartOrphanComponentIfParentAppeared();
    void startupComponents_shouldStartOrphanComponentsWhenParentsAppeared();
    void startupComponents_shouldNotStartOrphanComponentsWhenOtherParentsAppeared();

    void shutdownAllComponents_shouldEmit();
    void shutdownAllComponents_shouldEmitAboutSignal();
    void shutdownAllComponents_shouldRemoveThemFromStartedList();
    void shutdownAllComponents_shouldAddThemToTheStoppedList();
    void shutdownAllComponents_shouldNotShutdownUnexistingComponent();
    void shutdownAllComponents_shouldNotShutdownBuiltInComponent();
    void shutdown_shouldShutdownAllComponents();
    void shutdown_shouldShutdownBuiltInComponents();

    // Integration tests:
    void startupComponent_shouldPassRightComponentsInRightOrder();
    void startupAllComponents_shouldPassComponentsInRightOrder();
    void startupAllComponents_shouldPassComponentsInRightOrder_ComplexDependencies();
    void shutdownComponent_shouldPassComponentsInReverseOrder();
    void shutdownAllComponents_shouldPassComponentsInRightOrder();
};

#endif // COMPONENTMANAGERTEST_H


